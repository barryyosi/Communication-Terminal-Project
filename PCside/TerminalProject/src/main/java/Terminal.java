import com.fazecast.jSerialComm.*;

import javax.swing.*;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;


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

    public static File filesDir = new File("C:\\Users\\bary_\\Documents\\university\\3rd year\\Semester B\\DCS\\Communication-Terminal-Project\\PCside\\TerminalProject\\src\\main\\Files");
    public static File[] listOfFiles = filesDir.listFiles();
    public static ArrayList<File> pcFiles = new ArrayList<File>(Arrays.stream(listOfFiles).toList());
    public static ArrayList<File> mcuFiles = new ArrayList<File>();

    // TODO - finalize this method.
    public static void getSerialPort(){

        //        for (SerialPort port : ports){
//            if(port.friendlyName == "UARTXXXSHIT"){
//
//            }
//        }
//          https://fazecast.github.io/jSerialComm/
        System.out.println();

    }

    // TODO - Finalize this method.
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
    public static void main(String[] args) throws IOException {
//        sysPort = SerialPort.getCommPort("PEMicro/Freescale - CDC Serial Port");
        sysPort = SerialPort.getCommPort("COM6");
        initNewSerialPort(9600);
        byte[] msg = {'b','a','r','r'};
        sysPort.closePort();
        var a = sysPort.getDeviceWriteBufferSize();
        sysPort.openPort();
        sysPort.writeBytes(msg, 4);
//        var b = sysPort.getOutputStream();
//        b.write(msg);
//        while(true)


//        TerminalGUI gui = new TerminalGUI();

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
