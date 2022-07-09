import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class TerminalGUI {
    JFrame terminalFrame;
    JPanel SleepModePanel;
    JPanel ChatModePanel;
    JPanel FileTransferPanel;
    JPanel TerminalConfigPanel;
    JMenuBar menuBar;
    JTextArea textArea;
    JTextPane textPane;

    public static final String PC = "PC";
    public static final String MCU = "MCU";

    private void initTerminalGUI() {
        //bCreating the Frame
        terminalFrame = new JFrame("Terminal");
        terminalFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        terminalFrame.setSize(400, 400);

        // Creating the MenuBar and adding components
        menuBar = new JMenuBar();
        JMenu m1 = new JMenu("Switch mode");
        menuBar.add(m1);

        JMenuItem m11 = new JMenuItem("Sleep mode");
        JMenuItem m12 = new JMenuItem("Chat mode");
        JMenuItem m13 = new JMenuItem("File Transfer mode");
        JMenuItem m14 = new JMenuItem("Terminal Configuration mode");
        JMenuItem m15 = new JMenuItem("Reset MCU");
        m1.add(m11);
        m1.add(m12);
        m1.add(m13);
        m1.add(m14);

        // Creating the panel at bottom and adding components
        SleepModePanel = new JPanel();       // the panel is not visible in output
        ChatModePanel = new JPanel();        // the panel is not visible in output
        FileTransferPanel = new JPanel();    // the panel is not visible in output
        TerminalConfigPanel = new JPanel();  // the panel is not visible in output

        initSleepModePanel();
        // Adding Components to the frame.
        terminalFrame.getContentPane().add(BorderLayout.NORTH, menuBar);
        terminalFrame.getContentPane().add(BorderLayout.CENTER, SleepModePanel);
//        terminalFrame.getContentPane().add(BorderLayout.CENTER, textArea);
//        chatPrint(PC,"barry is the king");

    }

    private void initChatModePanel(){

        JLabel label = new JLabel("Enter Message");
        JTextField textField = new JTextField(15); // accepts upto 15 characters
        JButton send = new JButton("Send");
        JButton reset = new JButton("Reset");
        textPane = new JTextPane();

        ChatModePanel.add(label);                           // Components Added using Flow Layout
        ChatModePanel.add(textField);
        ChatModePanel.add(textPane);
        ChatModePanel.add(send);
        ChatModePanel.add(reset);

        // Text Area at the Center
        textArea = new JTextArea();
    }

    private void initSleepModePanel(){
        JButton ChatModeButton = new JButton("Chat Mode");
        ChatModeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

            }
        });

        JButton FileTransferButton = new JButton("File Transfer Mode");
        FileTransferButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

            }
        });

        JButton TerminalConfigButton = new JButton("Terminal Configuration");
        TerminalConfigButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

            }
        });

        SleepModePanel.add(ChatModeButton);
        SleepModePanel.add(FileTransferButton);
        SleepModePanel.add(TerminalConfigButton);
    }
    private void chatPrint(String messageCommitter, String msg) {
        textArea.append( messageCommitter + ": " + msg +"\n");
    }

    public TerminalGUI() {

        initTerminalGUI();

        terminalFrame.setVisible(true);

    }

    public void changePane(Terminal.State argState) {
        switch (argState) {
            case Sleep: {

            }
            break;
            case Chat: {
                // TODO - implement
                // sysPort.serialRead();
            }
            break;

            case FileTransfer:
                // TODO - implement

            case TerminalConfig: {
                // TODO - pick port using gui
                // TODO - set baudRate using gui - port.setBaudRate(baud);
                Terminal.sysState = Terminal.State.Sleep;
            }
            break;
        }
    }
}
