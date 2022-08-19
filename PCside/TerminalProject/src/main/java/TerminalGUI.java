import com.fazecast.jSerialComm.SerialPort;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;


public class TerminalGUI {
    JFrame terminalFrame;
    JPanel SleepModePanel;
    JPanel ChatModePanel;
    JPanel FileTransferPanel;
    JPanel TerminalConfigPanel;
    JMenuBar menuBar;
    JTextArea textArea;

    public static final String PC = "PC";
    public static final String MCU = "MCU";
    private File[] pcFiles;
    private File[] mcuFiles;

    private void initTerminalGUI() throws IOException {
        // JFrame initialization.
        terminalFrame = new JFrame("Terminal");
        terminalFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        terminalFrame.setSize(400, 400);

        // Creating the MenuBar and adding menu items.
        menuBar = new JMenuBar();
        JMenu m1 = new JMenu("Switch mode");
        menuBar.add(m1);

        JMenuItem m11 = new JMenuItem("Sleep mode");
        m11.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.sysState = Terminal.State.Sleep;
                switchPane(SleepModePanel);

            }
        });

        JMenuItem m12 = new JMenuItem("Chat mode");
        m12.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.sysState = Terminal.State.Chat;
                switchPane(ChatModePanel);
            }
        });

        JMenuItem m13 = new JMenuItem("File Transfer mode");
        m13.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.sysState = Terminal.State.FileTransfer;
                switchPane(FileTransferPanel);

            }
        });

        JMenuItem m14 = new JMenuItem("Terminal Configuration mode");
        m14.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.sysState = Terminal.State.TerminalConfig;
                switchPane(TerminalConfigPanel);

            }
        });

        m1.add(m11);
        m1.add(m12);
        m1.add(m13);
        m1.add(m14);

        // Creating mode panels adding relevant components.
        SleepModePanel = new JPanel();
        ChatModePanel = new JPanel();
        FileTransferPanel = new JPanel();
        TerminalConfigPanel = new JPanel();

        terminalFrame.getContentPane().add(BorderLayout.NORTH, menuBar);

        // Initializing each mode panel.
        initChatModePanel();
        initFileTransferModePanel();
        initTerminalConfigModePanel();
        initSleepModePanel();

        // SleepMode panel appears on start up.
        terminalFrame.getContentPane().add(BorderLayout.CENTER, TerminalConfigPanel);
        terminalFrame.getContentPane().getComponent(1).setVisible(true);

    }
    private void initChatModePanel() throws IOException {
        // Creating chat mode panel and adding relevant components.
        textArea= new JTextArea(30, 30);

        JLabel label = new JLabel("Enter Message");
        JTextField textField = new JTextField(15); // accepts upto 15 characters

        JButton send = new JButton("Send");
        send.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                chatPrint(textArea,PC, textField.getText());
                String message = "PC:".concat(textField.getText());
                Terminal.sendFrame(message);
                textField.setText("");
            }
        });

        JButton reset = new JButton("Remove chat");
        reset.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                textArea.setText("");
            }
        });


//        BufferedImage mcuPushButtonReference = ImageIO.read(new File("src/main/Images/img3.jpeg"));
//        JLabel pbRefLabel = new JLabel(new ImageIcon(mcuPushButtonReference));

        ChatModePanel.add(label);
        ChatModePanel.add(textField);
        ChatModePanel.add(send);
        ChatModePanel.add(reset);
        ChatModePanel.add(BorderLayout.NORTH,textArea);
//        ChatModePanel.add(pbRefLabel);

    }
    private void initFileTransferModePanel() throws IOException {

        // Creating file transfer mode panel and adding relevant components.
        pcFiles = Terminal.pcFiles.toArray(new File[0]);
        mcuFiles = Terminal.mcuFiles.toArray(new File[0]);

        // PC Files box.
        Box pcFilesBox = Box.createVerticalBox();
        JLabel pcLabel = new JLabel("PC Files");
        DefaultListModel<File> pcf = new DefaultListModel<>();
        for (File file : pcFiles) pcf.addElement(file);
        JList<File> pcFileJList = new JList(pcf);
        pcFileJList.setPreferredSize(new Dimension(500, 200));
        pcFilesBox.add(pcLabel);
        pcFilesBox.add(pcFileJList);

        // MCU Files box.
        Box mcuFilesBox = Box.createVerticalBox();
        JLabel mcuLabel = new JLabel("MCU Files");
        DefaultListModel<File> mcuf = new DefaultListModel();
        for (File file : mcuFiles) mcuf.addElement(file);
        JList<File> mcuFileJList = new JList(mcuf);
        mcuFileJList.setPreferredSize(new Dimension(500, 200));
        mcuFilesBox.add(mcuLabel);
        mcuFilesBox.add(mcuFileJList);

        JButton reloadFiles = new JButton("Load PC files");
        reloadFiles.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.filesDir = new File("PCside/TerminalProject/src/main/PC2MCU");
                Terminal.listOfFiles = Terminal.filesDir.listFiles();
                Terminal.pcFiles = new ArrayList < File > (Arrays.stream(Terminal.listOfFiles).toList());
                pcFiles = Terminal.pcFiles.toArray(new File[0]);
                pcf.removeAllElements();
                for (File file : pcFiles) pcf.addElement(file);
//                for (File file : pcFiles) pcf.addElement(file);

//                for (File file : Terminal.pcFiles)
//                    if(!pcf.contains(file))
//                        pcf.addElement(file);
//                // TODO - verify this
//                for (DefaultListModel<File> file : Arrays.asList(pcf))
//                    if(Arrays.asList(pcFiles).contains(file))
//                        pcf.removeElement(file);
            }

        });

        Box transferBox = Box.createVerticalBox();
        JButton moveToPC = new JButton("PC << MCU");
        moveToPC.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                var selected = mcuFileJList.getSelectedValuesList();
                for (File file : selected){;
                    if (pcf.contains(file))
                        JOptionPane.showMessageDialog(null, "File already exist in PC");
                    else
                        pcf.addElement(file);
                }

            }
        });
        JButton moveToMCU = new JButton(" PC >> MCU ");
        moveToMCU.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                var selected = pcFileJList.getSelectedValuesList();
                for (File file : selected){
                    if (mcuf.contains(file))
                        JOptionPane.showMessageDialog(null, "File already exist in MCU");
                    else {
                        mcuf.addElement(file);
                        try { Terminal.sendFile(file); }
                        catch (IOException ex) { throw new RuntimeException(ex); }
                    }
                    }
                }
        });


        transferBox.add(moveToPC);
        transferBox.add(moveToMCU);


        FileTransferPanel.add(reloadFiles);
        FileTransferPanel.add(pcFilesBox);
        FileTransferPanel.add(transferBox);
        FileTransferPanel.add(mcuFilesBox);
//        FileTransferPanel.add(pbRefLabel);

    }
    private void initTerminalConfigModePanel() {

        // Available baud rates and com ports.
        String[] baudRates = {"2400", "9600", "19200", "38400"};

        SerialPort[] coms = Terminal.availablePorts;

        JLabel comLabel = new JLabel("COM ");
        JComboBox comDropdown = new JComboBox<>(coms);

        comDropdown.setSize(comDropdown.getPreferredSize());

        JLabel baudLabel = new JLabel("Baud rate ");
        JComboBox baudDropdown = new JComboBox<String>(baudRates);
        baudDropdown.setSize(comDropdown.getPreferredSize());

        JButton configButton = new JButton("Config");
        configButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                Terminal.sysBaudRate = Integer.parseInt((String)baudDropdown.getSelectedItem());
                if(Terminal.sysPort != null) Terminal.sendFrame((Terminal.sysBaudRate).toString());

                Terminal.sysPort = (SerialPort) comDropdown.getSelectedItem();
                JOptionPane.showMessageDialog(null, "Communication port and baud rate updated.");
                Terminal.initNewSerialPort(Terminal.sysBaudRate);   // Configuring a new serial port based on selected
                                                                    // parameters.
//                switchPane(SleepModePanel);
            }
        });

        // Aligning dropdowns with labels and within each other.
        Box baudBox = Box.createHorizontalBox();
        Box comBox = Box.createHorizontalBox();

        Box terminalConfigBox = Box.createVerticalBox();

        terminalConfigBox.add(baudBox);
        terminalConfigBox.add(comBox);
        terminalConfigBox.add(configButton);

        baudBox.add(baudLabel);
        baudBox.add(baudDropdown);

        comBox.add(comLabel);
        comBox.add(comDropdown);
        TerminalConfigPanel.add(terminalConfigBox);
    }
    private void initSleepModePanel() throws IOException {
        JButton ChatModeButton = new JButton("Chat Mode");
        ChatModeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.sysState = Terminal.State.Chat;
                switchPane(ChatModePanel);

            }
        });

        JButton FileTransferButton = new JButton("File Transfer Mode");
        FileTransferButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.sysState = Terminal.State.FileTransfer;
                switchPane(FileTransferPanel);

            }
        });

        JButton TerminalConfigButton = new JButton("Terminal Configuration");
        TerminalConfigButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.sysState = Terminal.State.TerminalConfig;
                switchPane(TerminalConfigPanel);

            }
        });

//        BufferedImage mcuPushButtonReference = ImageIO.read(new File("src/main/Images/img2.jpeg"));
//        JLabel pbRefLabel = new JLabel(new ImageIcon(mcuPushButtonReference));

        SleepModePanel.add(ChatModeButton);
        SleepModePanel.add(FileTransferButton);
        SleepModePanel.add(TerminalConfigButton);
//        SleepModePanel.add(pbRefLabel);
    }
    protected void chatPrint(JTextArea argTextArea,String messageCommitter, String msg) {
        argTextArea.append( messageCommitter + ": " + msg +"\n");
//        if(messageCommitter == PC)
//            Terminal.sendFrame(msg);
    }
    public TerminalGUI() throws IOException {

        initTerminalGUI();
        terminalFrame.setVisible(true);

    }

    public void switchPane(JPanel argPanel) {
        String message = Terminal.sysState.toString();
        Terminal.sendFrame(message);
        terminalFrame.getContentPane().removeAll();
        terminalFrame.repaint();
        terminalFrame.revalidate();
        terminalFrame.getContentPane().add(BorderLayout.NORTH, menuBar);
        terminalFrame.getContentPane().add(BorderLayout.CENTER, argPanel);
        terminalFrame.getContentPane().getComponent(1).setVisible(true);
        terminalFrame.repaint();
        terminalFrame.revalidate();

        }

    public void showMessageDialog(String s) {
        JOptionPane.showMessageDialog(null, s);
    }
}
