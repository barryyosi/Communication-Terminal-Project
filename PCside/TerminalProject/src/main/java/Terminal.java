import com.fazecast.jSerialComm.*;

import javax.swing.*;
import java.io.*;
import java.nio.file.Files;

import java.util.ArrayList;
import java.util.Arrays;

public class Terminal {
    private static final int MAX_STR_LEN = 32;
    private static final int EOS = '$'; // End of string character.
    public static SerialPort[] availablePorts = SerialPort.getCommPorts();

    protected static SerialPort sysPort;
    protected static Integer sysBaudRate;

    public static int msgIndex = 0;
    public static char[] mcuMessage = new char[MAX_STR_LEN];
    private static int STOP_BITS = 1;
    private static int DATA_BITS = 8;

    public enum State {
        Sleep,
        Chat,
        FileTransfer,
        TerminalConfig
    }
    public static State sysState = State.Sleep;

    public static File MCU2PC = new File("PCside/TerminalProject/src/main/MCU2PC");
    public static File filesDir = new File("PCside/TerminalProject/src/main/PC2MCU");

    public static File[] listOfFiles = filesDir.listFiles();
    public static ArrayList < File > pcFiles = new ArrayList < File > (Arrays.stream(listOfFiles).toList());

    public static ArrayList < File > mcu2pcFiles = new ArrayList < File > (Arrays.stream(MCU2PC.listFiles()).toList());
    public static ArrayList < File > mcuFiles = new ArrayList < File > ();

    private static String tempFileName = "";
    private static String tempFileContent = "";
    private static File tempFile;
    private static boolean readFileName = false;

    private static FileWriter writer = null;

    static TerminalGUI gui;

    static {
        try {
            gui = new TerminalGUI();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static SerialPortDataListener serialPortListener = new SerialPortDataListener() {
        @Override
        public int getListeningEvents() {
            return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
        }
        @Override
        public void serialEvent(SerialPortEvent event) {

            byte[] newData = event.getReceivedData();
            Character[] msg = new Character[newData.length];
            char currentChar;
            switch (sysState) {

                case Sleep: // Sleep Mode.
                    break;
                case Chat: // Chat mode message.
                {
                    for (int i = 0; i < newData.length; i++) {
                        System.out.println(sysState.toString() + ") received:" + (char) newData[i]);
                        currentChar = (char) newData[i];

                        if ((int) currentChar == EOS) {
                            mcuMessage[msgIndex++] = '\0';
                            gui.chatPrint(gui.textArea, TerminalGUI.MCU, new String(mcuMessage));
                            mcuMessage = new char[MAX_STR_LEN];
                            msgIndex = 0;
                        } else if (((int) currentChar >= 65 && (int) currentChar <= 90) || (int) currentChar >= 48 && (int) currentChar <= 57)
                            mcuMessage[msgIndex++] = currentChar;
                    }

                }
                break;
                case FileTransfer: // File Transfer mode - ACK, fileName or fileContent received.
                {
                    for (int i = 0; i < newData.length; i++) {
                        currentChar = (char) newData[i];
                        System.out.println(i + ") received: " + currentChar);
                    }
                    if (!readFileName) {
                        for (int i = 0; i < newData.length; i++) {
                            currentChar = (char) newData[i];
                            if (currentChar == '$') {
                                System.out.println(tempFileName + "read file name. ");
                                tempFile = new File(MCU2PC + "/" + tempFileName);
                                tempFileName = "";
                                tempFile.getParentFile().mkdirs();
                                try {
                                    tempFile.createNewFile();
                                    writer = new FileWriter(tempFile);
                                    readFileName = true;
                                    System.out.println(tempFileName + " open to write. ");
                                } catch (IOException e) {
                                    System.out.println("File Path: " + tempFile.getAbsolutePath());
                                    System.out.println(e.toString());
                                    throw new RuntimeException(e);
                                }

                            } else if (((int) currentChar >= 65 && (int) currentChar <= 122) || (int) currentChar >= 46 && (int) currentChar <= 57) {
                                System.out.println(tempFileName);
                                tempFileName += currentChar;
                                if (tempFileName.equals("ACK")) {
                                    tempFileName = "";
                                    gui.showMessageDialog("File transfer complete.");
                                }
                            }
                        }

                    } else { // Read file content

                        for (int i = 0; i < newData.length; i++) {
                            currentChar = (char) newData[i];
                            //                                System.out.println((++fileSize) + ") File byte received: " + currentChar);
                            if (currentChar == '$') {
                                System.out.println(tempFileContent);
                                try {
                                    writer.close();
                                    tempFileContent = "";
                                } catch (IOException e) {
                                    throw new RuntimeException(e);
                                }

                                readFileName = false;

                            } else {
                                try {
                                    if (currentChar != '\u0000')
                                        writer.append(currentChar);
                                    tempFileContent += currentChar;
                                } catch (IOException e) {
                                    throw new RuntimeException(e);
                                }
                            }
                        }

                    }
                }
                break;

            }
        }
    };

    public static void initNewSerialPort(int baud) {
        //        if (sysPort != null && sysPort.isOpen()) {
        //            //closePort();
        //        }
        int tempBaud = baud == 38400 ? 19200 : baud;
        sysPort.closePort();
        sysPort.openPort();
        sysPort.addDataListener(serialPortListener);
        sysPort.setParity(SerialPort.NO_PARITY);
        sysPort.setNumStopBits(STOP_BITS);
        sysPort.setNumDataBits(DATA_BITS);
        sysPort.setBaudRate(tempBaud);
        String message = sysPort.toString() + " connected with baud-rate: " + baud + ", stop-bits: " + STOP_BITS + ", data-bits: " + DATA_BITS + " and no-parity.";
        JOptionPane.showMessageDialog(null, message);

    }

    static boolean fileNameSent = false;
    public static void sendFile(File argFile) throws IOException {
        byte[] fileFrame;
        Integer stateOrdinal = sysState.ordinal(); // Each message/fileTransfer syncs system state with MCU

        String fileSize = String.format("%04d", argFile.length());
        String fileName = argFile.getName();
        sendFrame(fileName + fileSize);
        try {
            String fileContent = Files.readString(argFile.toPath());
            sendFrame(fileContent);
        } catch (IOException e) {
            String message = e.getMessage();
            JOptionPane.showMessageDialog(null, "Error sending file: \n" + message);
        }

    }
    public static void requestFile(File argFile) throws IOException {
        byte[] fileFrame;
        Integer stateOrdinal = sysState.ordinal(); // Each message/fileTransfer syncs system state with MCU

        String fileSize = String.format("%04d", argFile.length());
        String fileName = argFile.getName();
        sendFrame(fileName + fileSize);
        sendFrame("$");

    }

    public static void sendFrame(String msg) {
        byte[] frame;
        Integer stateOrdinal = sysState.ordinal(); // Each message syncs system state with MCU
        String msgLength = String.format("%04d", (msg.length()));
        String frameString = stateOrdinal.toString() + msgLength + msg;

        frame = frameString.toString().getBytes();
        System.out.println(frameString.toString());
        sysPort.writeBytes(frame, frame.length);

    }
    Terminal() {}
    public static void main(String[] args) {}

}