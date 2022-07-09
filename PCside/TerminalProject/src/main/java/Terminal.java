import com.fazecast.jSerialComm.*;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;


public class Terminal {
    private static SerialPort sysPort;
    private InputStream inputStream;
    private OutputStream outputStream;

    public enum State {Sleep, Chat, FileTransfer, TerminalConfig }
    public static State sysState = State.Sleep;
    public static File filesDir = new File("src/main/Files");
    public static ArrayList<File> files = new ArrayList<File>(Arrays.asList(filesDir.listFiles()));
    // TODO - finalize this method.
    public static SerialPort getSerialPort(){
        final SerialPort[] availablePorts = SerialPort.getCommPorts();

        for (SerialPort port : availablePorts)
            System.out.println(port.getDescriptivePortName());

        sysPort = availablePorts[0];
        //        for (SerialPort port : ports){
//            if(port.friendlyName == "UARTXXXSHIT"){
//
//            }
//        }
//          https://fazecast.github.io/jSerialComm/

        return availablePorts[0];
    }

    // TODO - Finalize this method.
    public static void initNewSerialPort(String name, int baud, int dataBits, int stopBits){
        if (sysPort != null && sysPort.isOpen()) {
            //closePort();
        }
        sysPort = SerialPort.getCommPort(name);
        sysPort.setParity(SerialPort.NO_PARITY);
        sysPort.setNumStopBits(stopBits);
        sysPort.setNumDataBits(dataBits);
        sysPort.setBaudRate(baud);
        //sysPort.addDataListener(this);
    }

    public static void main(String[] args) throws IOException {

//        final SerialPort port = getSerialPort();
//        initNewSerialPort(port.getDescriptivePortName(), 9600, 8,1);
        System.out.println(files);
        TerminalGUI gui = new TerminalGUI();

        while(true){

            switch (sysState){

                case Chat: {
                    // TODO - implement
                    // sysPort.serialRead();
                }break;

                case FileTransfer:
                    // TODO - implement

                case TerminalConfig:
                {
                    // TODO - pick port using gui
                    // TODO - set baudRate using gui - port.setBaudRate(baud);
                    sysState = State.Sleep;
                }break;
            }
        }

    }
}
