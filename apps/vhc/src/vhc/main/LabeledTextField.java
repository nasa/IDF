package vhc.main;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JTextField;

import org.jdesktop.swingx.JXLabel;
import org.jdesktop.swingx.JXPanel;

/**
 * a <code>JTextField</code> paired with a <code>JXLabel</code>, whose location
 * is specifiable
 *
 * @author Derek Bankieris
 */
public class LabeledTextField extends JXPanel {

    /** the label */
    public final JXLabel label = new JXLabel();

    /** the text field */
    public final JTextField textField;

    /** enueration for the location of the label relative to the text field */
    public enum Location {LEFT, RIGHT, TOP, BOTTOM};

    /**
     * creates a labeled text field with the specified text at the specified
     * location relative to the text field
     *
     * @param labelLocation the location of the label
     * @param labelText     the label text
     */
    public LabeledTextField(Location labelLocation, String labelText) {
        this(null, false, labelLocation, labelText);
    }

    /**
     * creates a labeled text field with the specified text at the specified
     * location relative to the specified text field
     *
     * @param textField     the text field to use
     * @param labelLocation the location of the label
     * @param labelText     the label text
     */
    public LabeledTextField(JTextField textField, Location labelLocation, String labelText) {
        this(textField, false, labelLocation, labelText);
    }

    /**
     * creates a labeled text field with the specified text at the specified
     * location relative to the text field, which will expand as specified
     *
     * @param expandTextField whether or not to expand the text field
     * @param labelLocation   the location of the label
     * @param labelText       the label text
     */
    public LabeledTextField(boolean expandTextField, Location labelLocation, String labelText) {
        this(null, expandTextField, labelLocation, labelText);
    }

    /**
     * creates a labeled text field with the specified text at the specified
     * location relative to the specified text field, which will expand as
     * specified
     *
     * @param textField       the text field to use
     * @param expandTextField whether or not to expand the text field
     * @param labelLocation   the location of the label
     * @param labelText       the label text
     */
    public LabeledTextField(JTextField textField, boolean expandTextField, Location labelLocation, String labelText) {
        super(new GridBagLayout());

        if (textField == null) {
            textField = new JTextField();
        }
        this.textField = textField;

        label.setText(labelText);

        configureLayout(expandTextField, labelLocation);
    }

    /**
     * configures the layout according to the specified parameters
     *
     * @param expandTextField whether or not to expand the text field
     * @param labelLocation   the location of the label
     */
    public void configureLayout(boolean expandTextField, Location labelLocation) {
        removeAll();

        GridBagConstraints constraints = new GridBagConstraints() {{
            gridx = gridy = 1;
        }};

        add(label, constraints);

        if (expandTextField) {
            constraints.fill = GridBagConstraints.HORIZONTAL;
            constraints.weightx = 1;
        }

        switch (labelLocation) {
            case LEFT:
                constraints.insets.left = 5;
                constraints.gridx = 2;
                break;
            case RIGHT:
                constraints.gridx = 0;
                break;
            case TOP:
                constraints.gridy = 2;
                break;
            case BOTTOM:
                constraints.gridy = 0;
                break;
        }

        add(textField, constraints);
    }

}
