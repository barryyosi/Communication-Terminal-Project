import com.fazecast.jSerialComm.*;

import javax.swing.*;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;

// TODO - Implement receive method.
public class Terminal {
    public static SerialPort[] availablePorts = SerialPort.getCommPorts();

    protected static SerialPort sysPort;
    protected static Integer sysBaudRate;
    private InputStream inputStream;
    private OutputStream outputStream;

    private static int STOP_BITS = 1;
    private static int DATA_BITS = 8;
    public enum State {Sleep, Chat, FileTransfer, TerminalConfig }
    public static State sysState = State.Sleep;

    // TODO - Make filesDir more OS generic
    public static File filesDir = new File("C:\\Users\\bary_\\Documents\\university\\3rd year\\Semester B\\DCS\\Communication-Terminal-Project\\PCside\\TerminalProject\\src\\main\\Files");
//    public static File filesDir = new File("src/main/Files");
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
    public void sendFile(File argFile){}
    // TODO - Implement this.
    public void recvFile(){}
    public static void sendFrame(String msg){
        byte[] frame;
        Integer stateOrdinal = sysState.ordinal();      // Each message syncs system state with MCU
        String frameString =  stateOrdinal.toString() + ((Integer)msg.length()).toString() + msg;

        frame = frameString.toString().getBytes();

//        System.out.println(frame);
        System.out.println("\n");
        for (byte argByte:frame) {
            System.out.print(((char)argByte) +"(" + argByte + ")" + "\t");
        }

        sysPort.writeBytes(frame, frame.length);
        // TODO - Implement Ack receive.
        // while(sysPort.readBytes){}
    }
    public static void main(String[] args) throws IOException {

        TerminalGUI gui = new TerminalGUI();
        sysPort = SerialPort.getCommPort("COM6");
        initNewSerialPort(9600);
        var a = sysPort.getDeviceWriteBufferSize();
        sysPort.closePort();
        sysPort.openPort();
        // Sync message
//        sysState = State.Chat;  // Test assignment


        //sysPort.writeBytes(msg, 4);
//        var b = sysPort.getOutputStream();
//        b.write(msg);
//        while(true)


//

//        while(true){
//
//            switch (sysState){
//
//                case Chat: {
//                    // TODO - implement
//                    // sysPort.serialRead();
//                }break;
//
//                case FileTransfer:
//                    // TODO - implement
//
//                case TerminalConfig:
//                {
//                    // TODO - pick port using gui
//                    // TODO - set baudRate using gui - port.setBaudRate(baud);
//                    sysState = State.Sleep;
//                }break;
//            }
//        }

    }
}
