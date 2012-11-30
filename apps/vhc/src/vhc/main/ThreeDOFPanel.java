package vhc.main;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.AbstractAction;
import javax.swing.SwingConstants;

import org.jdesktop.swingx.JXButton;
import org.jdesktop.swingx.JXPanel;

/**
 * a combination of one <code>ButtonGrid</code> and three
 * <code>LabeledSlider</code>s representing a control panel for three degress
 * of freedom. The layout contains a button to zero out the values and supports
 * full and light views.
 *
 * @author Derek Bankieris
 */
public class ThreeDOFPanel extends JXPanel {

    /** the first slider */
    public final LabeledSlider firstSlider;

    /** the second slider */
    public final LabeledSlider secondSlider;

    /** the third slider */
    public final LabeledSlider thirdSlider;

    /** the zeroing button */
    public final JXButton zeroButton = new JXButton(new AbstractAction() {
        {
        putValue(NAME, "Zero");
        putValue(SHORT_DESCRIPTION, "Zero all sliders.");
        }
        public void actionPerformed(ActionEvent e) {
            firstSlider.slider.setValue(0);
            secondSlider.slider.setValue(0);
            thirdSlider.slider.setValue(0);
        }
    });

    /** the button grid */
    public final ButtonGrid buttonGrid = new ButtonGrid() {{
        // cause button clicks to change the appropriate sliders' positions
        ActionListener actionListener = new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                Object source = event.getSource();

                if (source == northWestButton) {
                    thirdSlider.step(!thirdSlider.slider.getInverted());
                    secondSlider.step(secondSlider.slider.getInverted());
                }
                else if (source == northButton) {
                    thirdSlider.step(!thirdSlider.slider.getInverted());
                }
                else if (source == northEastButton) {
                    thirdSlider.step(!thirdSlider.slider.getInverted());
                    secondSlider.step(!secondSlider.slider.getInverted());
                }
                else if (source == westButton) {
                    secondSlider.step(secondSlider.slider.getInverted());
                }
                else if (source == centerLeftButton) {
                    firstSlider.step(!firstSlider.slider.getInverted());
                }
                else if (source == centerRightButton) {
                    firstSlider.step(firstSlider.slider.getInverted());
                }
                else if (source == eastButton) {
                    secondSlider.step(!secondSlider.slider.getInverted());
                }
                else if (source == southWestButton) {
                    thirdSlider.step(thirdSlider.slider.getInverted());
                    secondSlider.step(secondSlider.slider.getInverted());
                }
                else if (source == southButton) {
                    thirdSlider.step(thirdSlider.slider.getInverted());
                }
                else if (source == southEastButton) {
                    thirdSlider.step(thirdSlider.slider.getInverted());
                    secondSlider.step(!secondSlider.slider.getInverted());
                }
            }
        };
        northWestButton.addActionListener(actionListener);
        northButton.addActionListener(actionListener);
        northEastButton.addActionListener(actionListener);
        westButton.addActionListener(actionListener);
        centerLeftButton.addActionListener(actionListener);
        centerRightButton.addActionListener(actionListener);
        eastButton.addActionListener(actionListener);
        southWestButton.addActionListener(actionListener);
        southButton.addActionListener(actionListener);
        southEastButton.addActionListener(actionListener);
    }};

    /**
     * creates a 3DOF panel with the specified names for the three degrees
     * of freedom
     *
     * @param firstDOF  name for the first degree of freedom
     * @param secondDOF name for the second degree of freedom
     * @param thirdDOF  name for the third degree of freedom
     */
    public ThreeDOFPanel(String firstDOF, String secondDOF, String thirdDOF) {
        super(new GridBagLayout());

        this.firstSlider = new LabeledSlider(firstDOF);
        this.secondSlider = new LabeledSlider(secondDOF);
        this.thirdSlider = new LabeledSlider(thirdDOF);

        configureLayout(VirtualHandControllerMain.Layout.FULL);
    }

    /**
     * configures the layout
     *
     * @param layout the configuarion
     */
    public void configureLayout(VirtualHandControllerMain.Layout layout) {
        removeAll();
        switch (layout) {

            case FULL:
                firstSlider.configureLayout(SwingConstants.VERTICAL, LabeledTextField.Location.LEFT,
                  LabeledTextField.Location.TOP);
                secondSlider.configureLayout(SwingConstants.HORIZONTAL, LabeledTextField.Location.TOP,
                  LabeledTextField.Location.LEFT);
                thirdSlider.configureLayout(SwingConstants.VERTICAL, LabeledTextField.Location.RIGHT,
                  LabeledTextField.Location.TOP);

                GridBagConstraints constraints = new GridBagConstraints() {{
                    fill = GridBagConstraints.BOTH;
                    gridx = 1;
                }};
                add(secondSlider, constraints);
                constraints.gridx = 0;
                constraints.gridy = 1;
                add(firstSlider, constraints);
                constraints.gridx = 2;
                add(thirdSlider, constraints);
                constraints.gridx = 1;
                constraints.gridy = 2;
                add(zeroButton, constraints);
                constraints.gridy = 1;
                constraints.weightx = constraints.weighty = 1;
                add(buttonGrid, constraints);
                break;

            case LIGHT:
                firstSlider.configureLayout(SwingConstants.HORIZONTAL, LabeledTextField.Location.LEFT,
                  LabeledTextField.Location.TOP);
                secondSlider.configureLayout(SwingConstants.HORIZONTAL, LabeledTextField.Location.LEFT,
                  LabeledTextField.Location.TOP);
                thirdSlider.configureLayout(SwingConstants.HORIZONTAL, LabeledTextField.Location.LEFT,
                  LabeledTextField.Location.TOP);

                constraints = new GridBagConstraints() {{
                    gridx = 0;
                    weightx = weighty = 1;
                    fill = HORIZONTAL;
                }};
                add(firstSlider, constraints);
                add(secondSlider, constraints);
                add(thirdSlider, constraints);
                add(zeroButton, constraints);
                break;
        }
    }

}
