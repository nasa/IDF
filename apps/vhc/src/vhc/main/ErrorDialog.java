package vhc.main;

import java.awt.Component;
import java.awt.Dimension;

import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;

/**
 * <code>ErrorDialog</code> provide a resizable, scrollable <code>JDialog</code>
 * styled after the <code>JOptionPane</code> <code>ERROR_MESSAGE</code> dialog.
 *
 * @author Derek Bankieris
 */
public class ErrorDialog {

    /** the resizable dialog */
    JDialog dialog;

    /** the scrollable text area within the dialog */
    javax.swing.JTextArea textArea = new javax.swing.JTextArea() {{
        setLineWrap(true);
        setWrapStyleWord(true);
        setEditable(false);
    }};

    /** constructor */
    public ErrorDialog() {
        dialog = new JOptionPane(
          new JScrollPane() {{
              setPreferredSize(new Dimension(250, 150));
              setViewportView(textArea);
          }}, JOptionPane.ERROR_MESSAGE).createDialog(null, null);
        dialog.setResizable(true);
    }

    /**
     * displays the error message
     *
     * @param parent   the component relative to which the error dialog should
     *                 be centered
     * @param message  the message to be displayed. The actual displayed text
     *                 is retrieved via the parameter's
     *                 <code>toString</code> method.
     * @param title    the title to be displayed across the top of the dialog
     * 
     */
    public void displayError(Component parent, Object message, String title) {
        textArea.setText(message.toString());
        dialog.setTitle(title);
        dialog.setLocationRelativeTo(parent);
        dialog.setVisible(true);
    }

}
