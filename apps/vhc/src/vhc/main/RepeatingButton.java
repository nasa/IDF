package vhc.main;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.*;
import javax.swing.event.*;
import org.jdesktop.swingx.JXButton;


/**
 * <code>RepeatingButton</code> is a <code>JButton</code> which contains a timer
 * for firing events while the button is held down. There is a default
 * initial delay of 300ms before the first event is fired and a 60ms delay
 * between subsequent events. When the user holds the button down and moves
 * the mouse out from over the button, the timer stops, but if the user moves
 * the mouse back over the button without having released the mouse button,
 * the timer starts up again at the same delay rate. If the enabled state is
 * changed while the timer is active, it will be stopped.
 *
 * NOTE: The normal button behavior is that the action event is fired after
 * the button is released. It may be important to know then that this is
 * still the case. So in effect, listeners will get 1 more event then what
 * the internal timer fires. It's not a "bug", per se, just something to be
 * aware of. There seems to be no way to suppress the final event from
 * firing anyway, except to process all ActionListeners internally. But
 * realistically, it probably doesn't matter.
 */
public class RepeatingButton extends JXButton implements ActionListener, MouseListener, FocusListener {

    /**
     * The pressed state for this button.
     */
    private boolean pressed = false;

    /**
     * Flag to indicate that the button should fire events when held.
     * If false, the button is effectively a plain old JButton, but
     * there may be times when this feature might wish to be disabled.
     */
    private boolean repeatEnabled = true;

    /**
     * The hold-down timer for this button.
     */
    private Timer timer = null;

    /**
     * The delay between firings.
     */
    private int delay = 60;

    /**
     * The delay before repeated firings beings.
     */
    private int initialDelay = 300;

    /**
     * Holder of the modifiers used when the mouse pressed the button.
     * This is used for subsequently fired action events. This may change
     * after mouse pressed if the user moves the mouse out, releases a key
     * and then moves the mouse back in.
     */
    private int modifiers = 0;

    /**
     * Creates a button with no set text or icon.
     */
    public RepeatingButton() {
        super();
        init();
    }

    /**
     * Creates a button where properties are taken from the Action supplied.
     *
     * @param a the button action
     */
    public RepeatingButton(Action a) {
        super(a);
        init();
    }

    /**
     * Creates a button with an icon.
     *
     * @param icon the button icon
     */
    public RepeatingButton(Icon icon) {
        super(icon);
        init();
    }

    /**
     * Creates a button with text.
     *
     * @param text the button text
     */
    public RepeatingButton(String text) {
        super(text);
        init();
    }

    /**
     * Creates a button with initial text and an icon.
     *
     * @param text the button text
     * @param icon the button icon
     */
    public RepeatingButton(String text, Icon icon) {
        super(text, icon);
        init();
    }

    /**
     * Initializes the button.
     */
    private void init() {
        this.addMouseListener(this);
        this.addFocusListener(this);
        // initialize timers for button holding...
        this.timer = new Timer(this.delay, this);
        this.timer.setRepeats(true);
    }

    /**
     * Gets the delay for the timer of this button.
     *
     * @return the delay
     */
    public int getDelay() {
        return this.delay;
    }

    /**
     * Set the delay for the timer of this button.
     *
     * @param d the delay
     */
    public void setDelay(int d) {
        this.delay = d;
    }

    /**
     * Gets the initial delay for the timer of this button.
     *
     * @return the initial delay
     */
    public int getInitialDelay() {
        return this.initialDelay;
    }

    /**
     * Sets the initial delay for the timer of this button.
     *
     * @param d the initial delay
     */
    public void setInitialDelay(int d) {
        this.initialDelay = d;
    }

    /**
     * Checks if the button should fire events when held. If false, the
     * button is effectively a plain old JButton, but there may be times
     * when this feature might wish to be disabled.
     *
     * @return if true, the button should fire events when held
     */
    public boolean isRepeatEnabled() {
        return this.repeatEnabled;
    }

    /**
     * Sets if the button should fire events when held. If false, the
     * button is effectively a plain old JButton, but there may be times
     * when this feature might wish to be disabled. If false, it will
     * also stop the timer if it's running.
     *
     * @param en if true, the button should fire events when held
     */
    public void setRepeatEnabled(boolean en) {
        if(!en) {
            this.pressed = false;
            if(timer.isRunning()) {
                timer.stop();
            }
        }
        this.repeatEnabled = en;
    }

    /**
     * Sets the enabled state of this button. Overridden to stop the timer
     * if it's running.
     *
     * @param en if true, enables the button
     */
    public void setEnabled(boolean en) {
        if(en != super.isEnabled()) {
            this.pressed = false;
            if(timer.isRunning()) {
            timer.stop();
            }
        }
        super.setEnabled(en);
    }

    /**
     * Handle action events.
     *
     * @param ae the action event
     */
    public void actionPerformed(ActionEvent ae) {
        // process events only from this components
        if(ae.getSource() == this.timer) {
            ActionEvent event = new ActionEvent(this, ActionEvent.ACTION_PERFORMED, super.getActionCommand(),
              this.modifiers);
            super.fireActionPerformed(event);
        }
    }

    /**
     * Handle mouse clicked events.
     *
     * @param me the mouse event
     */
    public void mouseClicked(MouseEvent me) {
        // process events only from this components
        if(me.getSource() == this) {
            this.pressed = false;
            if(this.timer.isRunning()) {
                this.timer.stop();
            }
        }
    }

    /**
     * Handle mouse pressed events.
     *
     * @param me the mouse event
     */
    public void mousePressed(MouseEvent me) {
        // process events only from this components
        if(me.getSource() == this && this.isEnabled() && this.isRepeatEnabled()) {
            this.pressed = true;
            if(!this.timer.isRunning()) {
                this.modifiers = me.getModifiers();
                this.timer.setInitialDelay(this.initialDelay);
                this.timer.start();
            }
        }
    }

    /**
     * Handle mouse released events.
     *
     * @param me the mouse event
     */
    public void mouseReleased(MouseEvent me) {
        // process events only from this components
        if(me.getSource() == this) {
            this.pressed = false;
            if(this.timer.isRunning()) {
                this.timer.stop();
            }
        }
    }

    /**
     * Handle mouse entered events.
     *
     * @param me the mouse event
     */
    public void mouseEntered(MouseEvent me) {
        // process events only from this components
        if(me.getSource() == this && this.isEnabled() && this.isRepeatEnabled()) {
            if(this.pressed && !this.timer.isRunning()) {
                this.modifiers = me.getModifiers();
                this.timer.setInitialDelay(this.delay);
                this.timer.start();
            }
        }
    }

    /**
     * Handle mouse exited events.
     *
     * @param me the mouse event
     */
    public void mouseExited(MouseEvent me) {
        // process events only from this components
        if(me.getSource() == this) {
            if(this.timer.isRunning()) {
                this.timer.stop();
            }
        }
    }

    /**
     * Handle focus lost events.
     *
     * @param fe the focus event
     */
    public void focusLost(FocusEvent fe) {
        if (fe.getSource() == this) {
            this.pressed = false;
            if (this.timer.isRunning()) {
                this.timer.stop();
            }
        }
    }

    /**
     * Handle focus gained events.
     *
     * @param fe the focus event
     */
    public void focusGained(FocusEvent fe) {}

}
