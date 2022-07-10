import com.fazecast.jSerialComm.SerialPort;

import javax.swing.*;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;


public class TerminalGUI {
    JFrame terminalFrame;
    CardLayout cardLayout;
    JPanel SleepModePanel;
    JPanel ChatModePanel;
    JPanel FileTransferPanel;
    JPanel TerminalConfigPanel;
    JMenuBar menuBar;

    JTextPane textPane;

    public static final String PC = "PC";
    public static final String MCU = "MCU";

    private void initTerminalGUI() {
        //bCreating the Frame

        terminalFrame = new JFrame("Terminal");
        terminalFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        terminalFrame.setSize(400, 400);
        cardLayout = new CardLayout();

        // Creating the MenuBar and adding components
        menuBar = new JMenuBar();
        JMenu m1 = new JMenu("Switch mode");
        menuBar.add(m1);

        JMenuItem m11 = new JMenuItem("Sleep mode");
        m11.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switchPane(SleepModePanel);
            }
        });

        JMenuItem m12 = new JMenuItem("Chat mode");
        m12.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switchPane(ChatModePanel);
            }
        });

        JMenuItem m13 = new JMenuItem("File Transfer mode");
        m13.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switchPane(FileTransferPanel);
            }
        });

        JMenuItem m14 = new JMenuItem("Terminal Configuration mode");
        m14.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switchPane(TerminalConfigPanel);
            }
        });

        m1.add(m11);
        m1.add(m12);
        m1.add(m13);
        m1.add(m14);

        // Creating the panel at bottom and adding components
        SleepModePanel = new JPanel();       // the panel is not visible in output
        ChatModePanel = new JPanel();        // the panel is not visible in output
        FileTransferPanel = new JPanel();    // the panel is not visible in output
        TerminalConfigPanel = new JPanel();  // the panel is not visible in output

        terminalFrame.getContentPane().add(BorderLayout.NORTH, menuBar);


        initChatModePanel();
        initFileTransferModePanel();
        initTerminalConfigModePanel();
        initSleepModePanel();
        terminalFrame.getContentPane().add(BorderLayout.CENTER, SleepModePanel);
        terminalFrame.getContentPane().getComponent(1).setVisible(true);





//        // Adding Components to the frame.

//        terminalFrame.getContentPane().add(BorderLayout.CENTER, textArea);
//        chatPrint(PC,"barry is the king");

    }
    private void initChatModePanel(){
        JTextArea textArea = new JTextArea(30, 30);
        JLabel label = new JLabel("Enter Message");
        JTextField textField = new JTextField(15); // accepts upto 15 characters
        JButton send = new JButton("Send");
        send.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                chatPrint(textArea,PC, textField.getText());
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


        ChatModePanel.add(label);                           // Components Added using Flow Layout
        ChatModePanel.add(textField);
        ChatModePanel.add(send);
        ChatModePanel.add(reset);
        ChatModePanel.add(BorderLayout.NORTH,textArea);

    }
    private void initFileTransferModePanel(){

        var pcFiles = Terminal.pcFiles.toArray(new File[0]);
        var mcuFiles = Terminal.mcuFiles.toArray(new File[0]);

        Box pcFilesBox = Box.createVerticalBox();
        JLabel pcLabel = new JLabel("PC Files");
        DefaultListModel<File> pcf = new DefaultListModel();
        for (File file : pcFiles) {
            pcf.addElement(file);
        }
        JList<File> pcFileJList = new JList(pcf);
        pcFileJList.setPreferredSize(new Dimension(850, 200));

        pcFilesBox.add(pcLabel);
        pcFilesBox.add(pcFileJList);

        Box mcuFilesBox = Box.createVerticalBox();
        JLabel mcuLabel = new JLabel("MCU Files");
        DefaultListModel<File> mcuf = new DefaultListModel();
        for (File file : mcuFiles) {
            pcf.addElement(file);
        }

        JList<File> mcuFileJList = new JList(mcuf);
        mcuFileJList.setPreferredSize(new Dimension(850, 200));

        mcuFilesBox.add(mcuLabel);
        mcuFilesBox.add(mcuFileJList);

        JButton reloadFiles = new JButton("Load files");
        reloadFiles.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                // TODO - Implement reloading files
            }
        });

        Box transferBox = Box.createVerticalBox();

        JButton moveToPC = new JButton("<<");
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
//
                // TODO - Implement actual file transfer using UART

            }
        });
        JButton moveToMCU = new JButton(">>");
        moveToMCU.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                var selected = pcFileJList.getSelectedValuesList();
                for (File file : selected){
                    if (mcuf.contains(file))
                        JOptionPane.showMessageDialog(null, "File already exist in MCU");
                    else
                        mcuf.addElement(file);
                    // TODO - Implement actual file transfer using UART
                }

            }
        });

        JButton removeFromMCU = new JButton(" - ");
        removeFromMCU.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                var selected = mcuFileJList.getSelectedValuesList();
                if(selected.isEmpty())
                    JOptionPane.showMessageDialog(null, "Pick files to remove from MCU");
                else {
                    for (File file : selected) {
                        mcuf.removeElement(file);
                        JOptionPane.showMessageDialog(null, "File removed from MCU");
                        // TODO - Implement actual file transfer using UART
                    }
                }

            }
        });

        transferBox.add(moveToPC);
        transferBox.add(moveToMCU);
        transferBox.add(removeFromMCU);


        FileTransferPanel.add(reloadFiles);
        FileTransferPanel.add(pcFilesBox);
//        FileTransferPanel.add(BorderLayout.CENTER,moveToPC);
//        FileTransferPanel.add(BorderLayout.NORTH ,moveToMCU);
        FileTransferPanel.add(transferBox);
        FileTransferPanel.add(mcuFilesBox);

    }
    private void initTerminalConfigModePanel(){

        // BaudRate and port to be configured to the Serial Port
        Integer selectedBaud = 9600;    // Default baud is set.
        SerialPort selectedPort = Terminal.sysPort;
        String[] baudRates = {"2400", "9600", "19200", "38400"};

        SerialPort[] coms = Terminal.availablePorts;


        JLabel comLabel = new JLabel("COM ");
        JComboBox comDropdown = new JComboBox<>(coms);
        comDropdown.setSize(comDropdown.getPreferredSize());
        comDropdown.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                // TODO - Implement reloading files
            }
        });

        JLabel baudLabel = new JLabel("Baud rate ");
        JComboBox baudDropdown = new JComboBox<String>(baudRates);
        baudDropdown.setSize(comDropdown.getPreferredSize());
        baudDropdown.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            }
        });

        JButton configButton = new JButton("Config");
        configButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Terminal.sysPort = (SerialPort) comDropdown.getSelectedItem();
                Terminal.sysBaudRate = Integer.parseInt((String)baudDropdown.getSelectedItem());

                JOptionPane.showMessageDialog(null, "Communication port and baud rate updated.");
                Terminal.initNewSerialPort(Terminal.sysBaudRate);
            }
        });

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
//        TerminalConfigPanel.add(baudLabel);
//        TerminalConfigPanel.add(baudBox);
//        TerminalConfigPanel.add(comsLabel);
//        TerminalConfigPanel.add(comsBox);
        TerminalConfigPanel.add(terminalConfigBox);
    }
    private void initSleepModePanel(){
        JButton ChatModeButton = new JButton("Chat Mode");
        ChatModeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switchPane(ChatModePanel);
            }
        });

        JButton FileTransferButton = new JButton("File Transfer Mode");
        FileTransferButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switchPane(FileTransferPanel);
            }
        });

        JButton TerminalConfigButton = new JButton("Terminal Configuration");
        TerminalConfigButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                switchPane(TerminalConfigPanel);
            }
        });

        SleepModePanel.add(ChatModeButton);
        SleepModePanel.add(FileTransferButton);
        SleepModePanel.add(TerminalConfigButton);
    }
    private void chatPrint(JTextArea argTextArea,String messageCommitter, String msg) {
        argTextArea.append( messageCommitter + ": " + msg +"\n");

    }

    public TerminalGUI() {

        initTerminalGUI();
        terminalFrame.setVisible(true);

    }

    public void switchPane(JPanel argPanel) {

        terminalFrame.getContentPane().removeAll();
        terminalFrame.repaint();
        terminalFrame.revalidate();
        terminalFrame.getContentPane().add(BorderLayout.NORTH, menuBar);
        terminalFrame.getContentPane().add(BorderLayout.CENTER, argPanel);
        terminalFrame.getContentPane().getComponent(1).setVisible(true);
        terminalFrame.repaint();
        terminalFrame.revalidate();

        }

}
