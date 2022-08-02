import com.fazecast.jSerialComm.*;

import javax.print.DocFlavor;
import javax.swing.*;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// TODO - Implement receive method.
public class Terminal {
    private static int MAX_STR_LEN = 32;
    private static int EOS = '$';     // End of string character.
    public static SerialPort[] availablePorts = SerialPort.getCommPorts();

    protected static SerialPort sysPort;
    protected static Integer sysBaudRate;

    private InputStream inputStream;
    private OutputStream outputStream;
    public static int msgIndex = 0;
    public static char[] mcuMessage = new char[MAX_STR_LEN];
    private static int STOP_BITS = 1;
    private static int DATA_BITS = 8;


    public enum State {Sleep, Chat, FileTransfer, TerminalConfig }
    public static State sysState = State.Sleep;

    // TODO - Make filesDir more OS generic
//    public static File filesDir = new File("C:\\Users\\bary_\\Documents\\university\\3rd year\\Semester B\\DCS\\Communication-Terminal-Project\\PCside\\TerminalProject\\src\\main\\Files");
//    public static File filesDir = new File("src/main/Files");
    public static File filesDir = new File("C:\\Users\\bary_\\Documents\\University\\DCS\\Communication-Terminal-Project\\PCside\\TerminalProject\\src\\main\\Files");
    public static File[] listOfFiles = filesDir.listFiles();
    public static ArrayList<File> pcFiles = new ArrayList<File>(Arrays.stream(listOfFiles).toList());
    public static ArrayList<File> mcuFiles = new ArrayList<File>();

    public static void initNewSerialPort(int baud){
        if (sysPort != null && sysPort.isOpen()) {
            //closePort();
        }
        sysPort.setParity(SerialPort.NO_PARITY);
        sysPort.setNumStopBits(STOP_BITS);
        sysPort.setNumDataBits(DATA_BITS);
        sysPort.setBaudRate(baud);
        String message = sysPort.toString() + " connected with baud-rate: " + baud + ", stop-bits: " + STOP_BITS + ", data-bits: " + DATA_BITS + " and no-parity.";
        JOptionPane.showMessageDialog(null, message);

    }

    // TODO - Implement this.

    static boolean fileNameSent = false;
    public static void sendFile(File argFile) throws IOException {
        byte[] fileFrame;
        Integer stateOrdinal = sysState.ordinal();      // Each message/fileTransfer syncs system state with MCU

        String fileSize = String.format("%04d", argFile.length());
        String fileName = argFile.getName();
        sendFrame(fileName + fileSize);
        try {
            String fileContent = Files.readString(argFile.toPath());
            sendFrame(fileContent
            );
        }
        catch (IOException e){
            String message = e.getMessage();
            JOptionPane.showMessageDialog(null,"Error sending file: \n" + message);
        }

    }
    public void recvFile(){}

    // TODO - Might need to enhance to support other system modes.
    public static void sendFrame(String msg){
        byte[] frame;
        Integer stateOrdinal = sysState.ordinal();      // Each message syncs system state with MCU
        String msgLength = String.format("%02d", (msg.length()));
        String frameString =  stateOrdinal.toString() + msgLength + msg;

        frame = frameString.toString().getBytes();
        System.out.println(frameString.toString());
        // Debug: Printing sent frame
        /*        for (byte argByte:frame) {
            System.out.print(((char)argByte) +"(" + argByte + ")" + "\t");
        }
*/
        sysPort.writeBytes(frame, frame.length);

        // TODO - Implement Ack receive.
        // while(sysPort.readBytes){}
    }
    Terminal(){
//        mcuMessageList = new ArrayList<Character>();
    }
    public static void main(String[] args) throws IOException {

        TerminalGUI gui = new TerminalGUI();
        // TODO - config serialPort and baud-rate startup.
        sysPort = SerialPort.getCommPort("COM6");
        initNewSerialPort(9600);

        sysPort.closePort();
        sysPort.openPort();
        sysPort.addDataListener(new SerialPortDataListener() {
            @Override
            public int getListeningEvents(){
                return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
            }
            @Override
            public void serialEvent(SerialPortEvent event){

                byte[] newData = event.getReceivedData();
//                int msgSize = event.;
                Character[] msg = new Character[newData.length];
                char currentChar;
                for (int i = 0; i < newData.length; i++) {
                    currentChar = (char) newData[i];
                    if ((int)currentChar == EOS) {
                        mcuMessage[msgIndex++] = '\0';
                        gui.chatPrint(gui.textArea, TerminalGUI.MCU, new String(mcuMessage));
                        mcuMessage = new char[MAX_STR_LEN];
                        msgIndex = 0;
                    }
                    else if (((int)currentChar >= 65 && (int)currentChar <= 90) || (int)currentChar >= 48 && (int)currentChar <= 57)
                        mcuMessage[msgIndex++] = currentChar;

                    System.out.println(currentChar + " ascii value: " + (int)currentChar);
                }
//                String str = new String(mcuMessage);
//                System.out.println("\t message so far: " + str);

//                String mcuMessageStr = new String(msg);

//                System.out.println(mcuMessage.toString() + "Message size: " + mcuMessage.length);

//                if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE)
//                    return;
//                byte[] newData = new byte[sysPort.bytesAvailable()];
//                int tempName = sysPort.readBytes(newData, newData.length);
//                if (sysState == State.Chat){
//                    System.out.println("received STRING: " + newData.toString() + "\n" + "received int: " + tempName);
//                    gui.chatPrint(gui.textArea,gui.MCU, );
//                    String message = "PC:".concat(textField.getText());
                }
        });


    }
}
