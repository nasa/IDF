package vhc.main;

import java.awt.GridLayout;

import org.jdesktop.swingx.JXPanel;

/**
 * a three by three grid of ten buttons, with the center cell containing two buttons
 *
 * @author Derek Bankieris
 */
public class ButtonGrid extends JXPanel {

    public final ImageSizingButton northWestButton = new ImageSizingButton();
    public final ImageSizingButton northButton = new ImageSizingButton();
    public final ImageSizingButton northEastButton = new ImageSizingButton();
    public final ImageSizingButton westButton = new ImageSizingButton();
    public final ImageSizingButton centerLeftButton = new ImageSizingButton();
    public final ImageSizingButton centerRightButton = new ImageSizingButton();
    public final ImageSizingButton eastButton = new ImageSizingButton();
    public final ImageSizingButton southWestButton = new ImageSizingButton();
    public final ImageSizingButton southButton = new ImageSizingButton();
    public final ImageSizingButton southEastButton = new ImageSizingButton();

    public ButtonGrid() {
        super(new GridLayout(3, 3));

        // North Row
        add(northWestButton);
        add(northButton);
        add(northEastButton);

        // Center Row
        add(westButton);
        add(new JXPanel(new GridLayout()) {{
            add(centerLeftButton);
            add(centerRightButton);
        }});
        add(eastButton);

        // South Row
        add(southWestButton);
        add(southButton);
        add(southEastButton);
    }

}
