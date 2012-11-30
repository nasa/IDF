package vhc.main;

import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.text.NumberFormat;

import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.NumberFormatter;

import org.jdesktop.swingx.JXPanel;
import org.jdesktop.swingx.JXFormattedTextField;

/**
 * a <code>JSlider</code> paired with a {@link LabeledTextField}, whose
 * location is specifiable
 *
 * @author Derek Bankieris
 */
public class LabeledSlider extends JXPanel {

    /**
     * the step size to use when increment/decrementing via the
     * <code>step</code> function
     */     
    int step = 1;

    /** the labeled text field */
    public final LabeledTextField labeledTextField;

    /** the slider */
    public final JSlider slider;

    /** the text field to use in the formatted text field */
    public final JXFormattedTextField formattedTextField = new JXFormattedTextField() {{
        setHorizontalAlignment(JTextField.RIGHT);

        // allow only integers
        setFormatterFactory(new DefaultFormatterFactory() {{
            setDefaultFormatter(new NumberFormatter() {{
                setValueClass(Integer.class);
                ((NumberFormat)getFormat()).setGroupingUsed(false);
            }});
        }});

        // update slider if the text field's value changes
        addPropertyChangeListener("value", new PropertyChangeListener() {
            public void propertyChange(PropertyChangeEvent e) {
                slider.setValue(((Integer)getValue()).intValue());
            };
        });

        // select all the text when the text field gains focus
        addFocusListener(new FocusAdapter() {
            @Override
            public void focusGained(FocusEvent e) {
                // JXFormattedTextField already manipulates the selection when it gains focus, so we must ensure the
                // selectAll call is executed after it is done, or the selection won't hold
                SwingUtilities.invokeLater(new Runnable() {
                    public void run() {
                        selectAll();
                    }
                });
            }
        });
    }};

    /**
     * creates a labeled slider with a horizontal slider, the labeled text field
     * on top, and the label on the left
     */
    public LabeledSlider(String labelText) {
        this(labelText, JSlider.HORIZONTAL, LabeledTextField.Location.TOP, LabeledTextField.Location.LEFT);
    }

    /**
     * creates a labeled slider with the specified orientation, the labeled
     * text field with the specified text at the specified location relative to
     * the slider, and the label at the specified location relative to the text
     * field
     *
     * @param labelText                the label text
     * @param sliderOrientation        the slider orientation,
     *                                 <code>JSlider.HORIZONTAL</code> or
     *                                 <code>JSlider.VERTICAL</code>
     * @param labeledTextFieldLocation the labeled text field location
     * @param labelLocation            the label location
     */
    public LabeledSlider(String labelText, int sliderOrientation, LabeledTextField.Location labeledTextFieldLocation,
      LabeledTextField.Location labelLocation) {
        this(labelText, sliderOrientation, labeledTextFieldLocation, labelLocation, 0, 100);
    }

    /**
     * creates a labeled slider with the specified orientation and mimimum and
     * maximum values, the labeled text field with the specified text at the
     * specified location relative to the slider, and the label at the
     * specified location relative to the text field
     *
     * @param labelText                the label text
     * @param sliderOrientation        the slider orientation,
     *                                 <code>JSlider.HORIZONTAL</code> or
     *                                 <code>JSlider.VERTICAL</code>
     * @param labeledTextFieldLocation the labeled text field location
     * @param labelLocation            the label location
     * @param minimum                  the minimum value
     * @param maximum                  the maximum value
     */
    public LabeledSlider(String labelText, int sliderOrientation, LabeledTextField.Location labeledTextFieldLocation,
      LabeledTextField.Location labelLocation, int minimum, int maximum) {
        super(new GridBagLayout());

        // update text field if the slider's value changes
        labeledTextField = new LabeledTextField(formattedTextField, labelLocation, labelText);
        slider = new JSlider() {{
            addChangeListener(new ChangeListener() {
                public void stateChanged(ChangeEvent changeEvent) {
                    syncTextFieldToSlider();
                }
            });
        }};

        setRange(minimum, maximum);

        configureLayout(sliderOrientation, labeledTextFieldLocation, labelLocation);
    }

    /**
     * configure the layout
     *
     * @param sliderOrientation        the slider orientation,
     *                                 <code>JSlider.HORIZONTAL</code> or
     *                                 <code>JSlider.VERTICAL</code>
     * @param labeledTextFieldLocation the labeled text field location
     * @param labelLocation            the label location
     */
    public void configureLayout(int sliderOrientation, LabeledTextField.Location labeledTextFieldLocation,
      LabeledTextField.Location labelLocation) {
        removeAll();

        slider.setOrientation(sliderOrientation);
        labeledTextField.configureLayout(false, labelLocation);

        GridBagConstraints constraints = new GridBagConstraints() {{
            gridx = gridy = 1;
            fill = BOTH;
        }};

        if (sliderOrientation == SwingConstants.HORIZONTAL) {
            constraints.weighty = 1;
        }
        else {
            constraints.weightx = 1;
        }

        add(labeledTextField, constraints);

        if (sliderOrientation == SwingConstants.HORIZONTAL) {
            constraints.weightx = 1;
            constraints.weighty = 0;
        }
        else {
            constraints.weightx = 0;
            constraints.weighty = 1;
        }

        switch (labeledTextFieldLocation) {
            case LEFT:
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

        add(slider, constraints);
    }

    /**
     * set the slider's range
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     */
    public void setRange(int minimum, int maximum) {
        slider.setMinimum(minimum);
        slider.setMaximum(maximum);
        ((NumberFormatter)formattedTextField.getFormatter()).setMinimum(new Integer(slider.getMinimum()));
        ((NumberFormatter)formattedTextField.getFormatter()).setMaximum(new Integer(slider.getMaximum()));

        // set the formatted text field's size such that it can fully display the min and max
        formattedTextField.setPreferredSize(null);
        formattedTextField.setText(Integer.toString(slider.getMinimum()));
        formattedTextField.setMinimumSize(formattedTextField.getPreferredSize());
        formattedTextField.setText(Integer.toString(slider.getMaximum()));
        if (formattedTextField.getPreferredSize().width > formattedTextField.getMinimumSize().width) {
            formattedTextField.setMinimumSize(formattedTextField.getPreferredSize());
        }
        syncTextFieldToSlider();
        formattedTextField.setPreferredSize(formattedTextField.getMinimumSize());
        revalidate();
    }

    /**
     * synchronize the text field to the slider
     */
    private void syncTextFieldToSlider() {
        formattedTextField.setValue(new Integer(slider.getValue()));
    }

    /**
     * step the slider in the specified direction
     *
     * forward the direction
     */
    public void step(boolean forward) {
        slider.setValue(slider.getValue() + (forward ? step : -step));
    }

}
