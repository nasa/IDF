package vhc.main;

import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.AbstractButton;

/**
 * <code>ButtonListener</code> tracks the pressed state of an
 * <code>Abstract Button</code> and executes its <code>activeChanged</code>
 * method when that state changes.
 *
 * @author Derek Bankieris
 */
public abstract class ButtonListener {

    /**
     * enables calling of the <code>activeChanged</code> method when the
     * pressed state of the target button changes
     */
    boolean enabled = true;

    /**
     * <code>true</code> when the mouse has been pressed over the target
     * button and not yet released
     */
    boolean mouseDown = false;

    /** <code>true</code> when the target button is in the pressed state */
    boolean active = false;

    /**
     * if enabled, called when the pressed state of the target button changes
     *
     * @param active the pressed tate of the target button
     */
    abstract void activeChanged(boolean active);

    /**
     * constructor
     *
     * @param targetButton the button whose pressed state is to be tracked
     */
    public ButtonListener(AbstractButton targetButton) {
        targetButton.addFocusListener(new FocusAdapter() {
            @Override
            public void focusLost(FocusEvent e) {
                mouseDown = false;
                if (active) {
                    setActive(false);
                }
            }
        });

        targetButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                mouseDown = true;
                setActive(true);
            }
            @Override
            public void mouseReleased(MouseEvent e) {
                mouseDown = false;
                if (active) {
                    setActive(false);
                }
            }
            @Override
            public void mouseEntered(MouseEvent e) {
                if (mouseDown) {
                    setActive(true);
                }
            }
            @Override
            public void mouseExited(MouseEvent e) {
                if (mouseDown) {
                    setActive(false);
                }
            }
        });
    }

    /**
     * sets the field that tracks the pressed state of the target button and
     * calls the <code>activeChanged</code> method, if enabled
     *
     * @param active the pressed state of the target button
     *
     */
    void setActive(boolean active) {
        if (this.active != active) {
            this.active = active;
            if (enabled) {
                activeChanged(active);
            }
        }
    }

    /**
     * enables and disables calling of the <code>activeChanged<code> method
     * when the target button's pressed state changes
     *
     * @param enabled the enabled state
     */
    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    /**
     * returns whether or not the <code>activeChanged</code> method is called
     * when the target button's pressed state changes
     *
     * @return the enabled state
     */
    public boolean isEnabled() {
        return enabled;
    }

}
