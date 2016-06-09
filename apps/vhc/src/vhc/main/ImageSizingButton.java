package vhc.main;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.Timer;

/**
 * a RepeatingButton that resizes its image whenever it is itself
 * resized. For performance, the delay between the time the button is resized
 * and the image is resized is specifiable.
 *
 * @author Derek Bankieris
 */
public class ImageSizingButton extends RepeatingButton {

    /** the image to be displayed */
    Image image;

    /**
     * a timer that delays the resizing of the image after the button itself
     * is resized
     */
    Timer timer = new Timer(100, new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            if (image != null) {
                int width = getWidth() * 75 / 100;
                int height = getHeight() * 75 / 100;
                if (width < 1) {
                    width = 1;
                }
                if (height < 1) {
                    height = 1;
                }
                setIcon(new ImageIcon(image.getScaledInstance(width, height, Image.SCALE_SMOOTH)));
            }
        }
    }) {{
        setRepeats(false);
    }};

    /**
     * creates a button that resizes its image by the specified number of
     * miliseconds after it is itself resized
     *
     * @param delay the delay in milliseconds
     */
    public ImageSizingButton(int delay) {
        this();
        timer.setInitialDelay(delay);
    }

    /**
     * creates a button with a default delay of 100 ms
     */
    public ImageSizingButton() {
        addComponentListener(new ComponentAdapter() {
            public void componentResized(ComponentEvent e) {
                timer.restart();
            }
        });
    }

    /**
     * sets the image to be resized
     *
     * @param imageIcon the image
     */
    public void setImageIcon(ImageIcon imageIcon) {
        image = imageIcon.getImage();
        setIcon(imageIcon);
    }

}
