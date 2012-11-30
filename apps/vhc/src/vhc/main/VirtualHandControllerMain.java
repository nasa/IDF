package vhc.main;

import com.apple.eawt.AppEvent.PreferencesEvent;
import com.apple.eawt.AppEvent.AboutEvent;
import com.apple.eawt.Application;
import com.apple.eawt.AboutHandler;
import com.apple.eawt.PreferencesHandler;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Desktop;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.KeyboardFocusManager;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Rectangle;
import java.io.IOException;
import java.net.URI;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.List;

import javax.swing.AbstractAction;
import javax.swing.AbstractButton;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.ImageIcon;
import javax.swing.JCheckBox;
import javax.swing.JCheckBoxMenuItem;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButton;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.JSeparator;
import javax.swing.JSlider;
import javax.swing.JToggleButton;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.NumberFormatter;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;

import joptsimple.OptionParser;
import joptsimple.OptionSet;
import joptsimple.OptionSpec;

import org.jdesktop.application.Action;
import org.jdesktop.application.utils.SwingHelper;
import org.jdesktop.application.View;
import org.jdesktop.swingx.JXButton;
import org.jdesktop.swingx.JXFormattedTextField;
import org.jdesktop.swingx.JXLabel;
import org.jdesktop.swingx.JXPanel;
import org.jdesktop.swingx.JXRadioGroup;
import org.jdesktop.swingx.JXTextField;

import trick.common.RunTimeTrickApplication;

/**
 * virtual hand controller for interfacing with Trick simulations that support
 * a hand controller simulation object
 *
 * @author Derek Bankieris
 */
public class VirtualHandControllerMain extends RunTimeTrickApplication {

    /** enumeration for translation orientations */
    enum Translation {XYZ, XZY, YXZ, YZX, ZXY, ZYX};

    /** enumeration for rotation orientations */
    enum Rotation {RPY, RYP, PRY, PYR, YRP, YPR};

    /** enumeration for application behavior on disconnect */
    enum OnDisconnect {Close, Notify, Nothing};

    /** enumeration for layouts */
    public enum Layout {

        FULL(),
        LIGHT();

        /** the window's bounding rectangle */
        public Rectangle rectangle;

        /** the window's extended state */
        public int extendedState = JFrame.NORMAL;

    };

    /** the main panel */
    JXPanel mainPanel;

    /** the layout */
    Layout layout;

    /** dialog for configuring settings */
    JDialog aboutDialog;

    /** translational control panel */
    ThreeDOFPanel translationPanel;

    /** rotational control panel */
    ThreeDOFPanel rotationPanel;

    /** slider for x translations*/
    LabeledSlider xSlider;

    /** slider for y translations*/
    LabeledSlider ySlider;

    /** slider for z translations*/
    LabeledSlider zSlider;

    /** slider for roll rotations */
    LabeledSlider rollSlider;

    /** slider for pitch rotations */
    LabeledSlider pitchSlider;

    /** slider for yaw rotations */
    LabeledSlider yawSlider;

    /** orientation for the translation panel */
    Translation translationOrientation;

    /** orientation for the rotation panel */
    Rotation rotationOrientation;

    /** radio group for the grannularity controls */
    JXRadioGroup<JRadioButton> grannularityRadioGroup;

    /** radio group for the trigger controls */
    JXRadioGroup<JRadioButton> triggerRadioGroup;

    /** the rate hold button */
    JToggleButton rateHoldToggleButton;

    /** the rate hold button listener */
    ButtonListener rateHoldButtonListener;

    /** the trigger up button listener */
    ButtonListener triggerUpButtonListener;

    /** the trigger down button listener */
    ButtonListener triggerDownButtonListener;

    /** name of the hand controller simulation object */
    String simObjectName = "simulationPathTo.idfInputLayout";

    /** dialog for displaying errors */
    ErrorDialog errorDialog;

    // property keys
    static final String layoutKey = "layout";

    static final String fullStateKey = "fullState";
    static final String fullXKey = "fullX";
    static final String fullYKey = "fullY";
    static final String fullWidthKey = "fullWidth";
    static final String fullHeightKey = "fullHeight";

    static final String lightStateKey = "lightState";
    static final String lightXKey = "lightX";
    static final String lightYKey = "lightY";
    static final String lightWidthKey = "lightWidth";
    static final String lightHeightKey = "lightHeight";

    static final String simObjectNameKey = "simObjectName";

    static final String grannularityKey = "grannularity";
    static final String grannularityVisibleKey = "grannularityVisible";

    static final String toggleRateHoldKey = "toggleRateHold";
    static final String rateHoldKey = "rateHold";
    static final String rateHoldVisibleKey = "rateHoldVisible";

    static final String stickyTriggerKey = "stickyTrigger";
    static final String triggerKey = "trigger";
    static final String triggerVisibleKey = "triggerVisible";

    static final String translationOrientationKey = "translationOrientation";
    static final String rotationOrientationKey = "rotationOrientation";

    static final String invertXKey = "invertX";
    static final String invertYKey = "invertY";
    static final String invertZKey = "invertZ";
    static final String invertPitchKey = "invertPitch";
    static final String invertYawKey = "invertYaw";
    static final String invertRollKey = "invertRoll";

    static final String xMinKey = "xMin";
    static final String xMaxKey = "xMax";
    static final String xStepKey = "xStep";

    static final String yMinKey = "yMin";
    static final String yMaxKey = "yMax";
    static final String yStepKey = "yStep";

    static final String zMinKey = "zMin";
    static final String zMaxKey = "zMax";
    static final String zStepKey = "zStep";

    static final String pitchMinKey = "pitchMin";
    static final String pitchMaxKey = "pitchMax";
    static final String pitchStepKey = "pitchStep";

    static final String yawMinKey = "yawMin";
    static final String yawMaxKey = "yawMax";
    static final String yawStepKey = "yawStep";

    static final String rollMinKey = "rollMin";
    static final String rollMaxKey = "rollMax";
    static final String rollStepKey = "rollStep";

    @Override
    protected void parseArguments(String[] arguments, OptionParser optionParser) {
        OptionSpec<String> layoutSpec = optionParser.accepts(layoutKey, "[full, light]").withRequiredArg();

        OptionSpec<Boolean> fullMaximizedSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add("fullMaximized"); add("fm");}},
          "Whether or not the window is maximized in the Full layout.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Integer> fullXSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(fullXKey); add("fx");}},
          "X position of the window when in the unmaximized Full layout.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> fullYSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(fullYKey); add("fy");}},
          "Y position of the window when in the unmaximized Full layout.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> fullWidthSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(fullWidthKey); add("fw");}},
          "Width of the window when in the unmaximized Full layout.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> fullHeightSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(fullHeightKey); add("fh");}},
          "Height of the window when in the unmaximized Full layout.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Boolean> lightMaximizedSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add("lightMaximized"); add("lm");}},
          "Whether or not the window is maximized in the Light layout.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Integer> lightXSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(lightXKey); add("lx");}},
          "X position of the window when in the unmaximized Light layout.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> lightYSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(lightYKey); add("ly");}},
          "Y position of the window when in the unmaximized Light layout.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> lightWidthSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(lightWidthKey); add("lw");}},
          "Width of the window when in the unmaximized Light layout.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> lightHeightSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(lightHeightKey); add("lh");}},
          "Height of the window when in the unmaximized Light layout.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<String> simObjectNameSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add(simObjectNameKey); add("name");}},
          "Simulation variable name of the Input Layout that this application will manipulate.").withRequiredArg();

        /*OptionSpec<String> grannularitySpec =
          optionParser.accepts(grannularityKey, "[corase, fine] Grannularity of the controls.").withRequiredArg();

        OptionSpec<Boolean> grannularityVisibleSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add(grannularityVisibleKey); add("gv");}},
          "Visibility of the Grannularity controls.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> toggleRateHoldSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add(toggleRateHoldKey); add("trh");}},
          "If true, the Rate Hold button will toggle when clicked.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> rateHoldSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(rateHoldKey); add("rh");}},
          "If true, the Rate Hold button will initialize as active. Use of this option sets --" +
          toggleRateHoldKey + "=true").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> rateHoldVisibleSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add(rateHoldVisibleKey); add("rhv");}},
          "Visibility of the Rate Hold button.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> stickyTriggerSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add(stickyTriggerKey); add("st");}},
          "If true, the trigger buttons will stick when clicked.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<String> triggerSpec = optionParser.accepts(triggerKey,
          "[up, neutral, down] Specifies the trigger's initial position. Use of this option sets --" +
          stickyTriggerKey + "=true").withRequiredArg();

        OptionSpec<Boolean> triggerVisibleSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add(triggerVisibleKey); add("tv");}},
          "Visibility of the Trigger controls.").withRequiredArg().ofType(Boolean.class);*/

        OptionSpec<String> translationOrientationSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add(translationOrientationKey); add("to");}},
          "[xyz, xzy, yxz, yzx, zxy, zyx] The orientation of the translation panel.").withRequiredArg();

        OptionSpec<String> rotationOrientationSpec =
          optionParser.acceptsAll(new ArrayList<String>() {{add(rotationOrientationKey); add("ro");}},
          "[pyr, pry, ypr, yrp, rpy, ryp] The orientation of the rotation panel.").withRequiredArg();

        OptionSpec<Boolean> invertXSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(invertXKey); add("xi");}},
          "Inversion of the x slider.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> invertYSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(invertYKey);add("yi");}},
          "Inversion of the y slider.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> invertZSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(invertZKey); add("zi");}},
          "Inversion of the z slider.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> invertPitchSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(invertPitchKey); add("pi");}},
          "Inversion of the pitch slider.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> invertYawSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(invertYawKey); add("wi");}},
          "Inversion of the yaw slider.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Boolean> invertRollSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(invertRollKey); add("ri");}},
          "Inversion of the roll slider.").withRequiredArg().ofType(Boolean.class);

        OptionSpec<Integer> xMinSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(xMinKey); add("xm");}},
          "The minimum value that the x slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> xMaxSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(xMaxKey); add("xM");}},
          "The maximum value that the x slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> xStepSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(xStepKey); add("xs");}},
          "The step size by which the x slider is incremented/decremented when a button is clicked.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> yMinSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(yMinKey); add("ym");}},
          "The minimum value that the y slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> yMaxSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(yMaxKey); add("yM");}},
          "The maximum value that the y slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> yStepSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(yStepKey); add("ys");}},
          "The step size by which the y slider is incremented/decremented when a button is clicked.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> zMinSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(zMinKey); add("zm");}},
          "The minimum value that the z slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> zMaxSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(zMaxKey); add("zM");}},
          "The maximum value that the z slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> zStepSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(zStepKey); add("zs");}},
          "The step size by which the z slider is incremented/decremented when a button is clicked.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> pitchMinSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(pitchMinKey); add("pm");}},
          "The minimum value that the pitch slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> pitchMaxSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(pitchMaxKey); add("pM");}},
          "The maximum value that the pitch slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> pitchStepSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(pitchStepKey); add("ps");}},
          "The step size by which the pitch slider is incremented/decremented when a button is clicked.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> yawMinSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(yawMinKey); add("wm");}},
          "The minimum value that the yaw slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> yawMaxSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(yawMaxKey); add("wM");}},
          "The maximum value that the yaw slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> yawStepSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(yawStepKey); add("ws");}},
          "The step size by which the yaw slider is incremented/decremented when a button is clicked.")
          .withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> rollMinSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(rollMinKey);add("rm");}},
          "The minimum value that the roll slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> rollMaxSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(rollMaxKey); add("rM");}},
          "The maximum value that the roll slider may take.").withRequiredArg().ofType(Integer.class);

        OptionSpec<Integer> rollStepSpec = optionParser.acceptsAll(new ArrayList<String>() {{add(rollStepKey); add("rs");}},
          "The step size by which the roll slider is incremented/decremented when a button is clicked.")
          .withRequiredArg().ofType(Integer.class);

        // The superclass handles all malformed arguments.
        super.parseArguments(arguments, optionParser);

        // This repeats some of the parsing done by the superclass, but there's
        // not a clean way of passing the results down, so live with it for now.
        OptionSet options = optionParser.parse(arguments);

        if (options.has(simObjectNameKey)) {
            trickProperties.setProperty(simObjectNameKey, options.valueOf(simObjectNameSpec));
        }

        /*if (options.has(grannularityKey)) {
            String grannularity = options.valueOf(grannularitySpec);
            if (grannularity.equalsIgnoreCase("coarse")) {
                trickProperties.setProperty(grannularityKey, "0");
            }
            else if (grannularity.equalsIgnoreCase("fine")) {
                trickProperties.setProperty(grannularityKey, "1");
            }
            else {
                System.out.println("Option ['grannularity'] argument must be one of ['coarse', 'fine']");
                System.exit(0);
            }
        }

        if (options.has(grannularityVisibleKey)) {
            trickProperties.setProperty(grannularityVisibleKey,
              Boolean.toString(options.valueOf(grannularityVisibleSpec)));
        }

        if (options.has(toggleRateHoldKey)) {
            boolean toggle = options.valueOf(toggleRateHoldSpec);
            trickProperties.setProperty(toggleRateHoldKey, Boolean.toString(toggle));
            // If toggling is disabled, start in the non-pressed state.
            if (!toggle) {
                trickProperties.setProperty(rateHoldKey, Boolean.toString(false));
            }
        }

        if (options.has(rateHoldKey)) {
            trickProperties.setProperty(toggleRateHoldKey, Boolean.toString(true));
            trickProperties.setProperty(rateHoldKey, Boolean.toString(options.valueOf(rateHoldSpec)));
        }

        if (options.has(rateHoldVisibleKey)) {
            trickProperties.setProperty(rateHoldVisibleKey, Boolean.toString(options.valueOf(rateHoldVisibleSpec)));
        }

        if (options.has(stickyTriggerKey)) {
            boolean sticky = options.valueOf(stickyTriggerSpec);
            trickProperties.setProperty(stickyTriggerKey, Boolean.toString(sticky));
            // If sticking is disabled, start in the neutral state.
            if (!sticky) {
                trickProperties.setProperty(triggerKey, "1");
            }
        }

        if (options.has(triggerKey)) {
            trickProperties.setProperty(stickyTriggerKey, Boolean.toString(true));
            String trigger = options.valueOf(triggerSpec);
            if (trigger.equalsIgnoreCase("up")) {
                trickProperties.setProperty(triggerKey, "0");
            }
            else if (trigger.equalsIgnoreCase("neutral")) {
                trickProperties.setProperty(triggerKey, "1");
            }
            else if (trigger.equalsIgnoreCase("down")) {
                trickProperties.setProperty(triggerKey, "2");
            }
            else {
                System.out.println("Option ['trigger'] argument must be one of ['up', 'neutral', 'down']");
                System.exit(0);
            }
        }

        if (options.has(triggerVisibleKey)) {
            trickProperties.setProperty(triggerVisibleKey, Boolean.toString(options.valueOf(triggerVisibleSpec)));
        }*/

        if (options.has(translationOrientationKey)) {
            String translation = options.valueOf(translationOrientationSpec);
            if (translation.equalsIgnoreCase("xyz")) {
                trickProperties.setProperty(translationOrientationKey, Translation.XYZ.toString());
            }
            else if (translation.equalsIgnoreCase("xzy")) {
                trickProperties.setProperty(translationOrientationKey, Translation.XZY.toString());
            }
            else if (translation.equalsIgnoreCase("yxz")) {
                trickProperties.setProperty(translationOrientationKey, Translation.YXZ.toString());
            }
            else if (translation.equalsIgnoreCase("yzx")) {
                trickProperties.setProperty(translationOrientationKey, Translation.YZX.toString());
            }
            else if (translation.equalsIgnoreCase("zxy")) {
                trickProperties.setProperty(translationOrientationKey, Translation.ZXY.toString());
            }
            else if (translation.equalsIgnoreCase("zyx")) {
                trickProperties.setProperty(translationOrientationKey, Translation.ZYX.toString());
            }
            else {
                System.out.println("Option ['translationOrientation'] argument must be one of" + 
                 " ['xyz', 'xzy', 'yxz', 'yzx', 'zxy', 'zyx']");
                System.exit(0);
            }
        }

        if (options.has(rotationOrientationKey)) {
            String rotation = options.valueOf(rotationOrientationSpec);
            if (rotation.equalsIgnoreCase("pyr")) {
                trickProperties.setProperty(rotationOrientationKey, Rotation.PYR.toString());
            }
            else if (rotation.equalsIgnoreCase("pry")) {
                trickProperties.setProperty(rotationOrientationKey, Rotation.PRY.toString());
            }
            else if (rotation.equalsIgnoreCase("ypr")) {
                trickProperties.setProperty(rotationOrientationKey, Rotation.YPR.toString());
            }
            else if (rotation.equalsIgnoreCase("yrp")) {
                trickProperties.setProperty(rotationOrientationKey, Rotation.YRP.toString());
            }
            else if (rotation.equalsIgnoreCase("rpy")) {
                trickProperties.setProperty(rotationOrientationKey, Rotation.RPY.toString());
            }
            else if (rotation.equalsIgnoreCase("ryp")) {
                trickProperties.setProperty(rotationOrientationKey, Rotation.RYP.toString());
            }
            else {
                System.out.println("Option ['rotationOrientation'] argument must be one of" + 
                 " ['pyr', 'pry', 'ypr', 'yrp', 'rpy', 'ryp']");
                System.exit(0);
            }
        }

        if (options.has(invertXKey)) {
            trickProperties.setProperty(invertXKey, Boolean.toString(options.valueOf(invertXSpec)));
        }

        if (options.has(invertYKey)) {
            trickProperties.setProperty(invertYKey, Boolean.toString(options.valueOf(invertYSpec)));
        }

        if (options.has(invertZKey)) {
            trickProperties.setProperty(invertZKey, Boolean.toString(options.valueOf(invertZSpec)));
        }

        if (options.has(invertPitchKey)) {
            trickProperties.setProperty(invertPitchKey, Boolean.toString(options.valueOf(invertPitchSpec)));
        }

        if (options.has(invertYawKey)) {
            trickProperties.setProperty(invertYawKey, Boolean.toString(options.valueOf(invertYawSpec)));
        }

        if (options.has(invertRollKey)) {
            trickProperties.setProperty(invertRollKey, Boolean.toString(options.valueOf(invertRollSpec)));
        }

        if (options.has(xMinKey)) {
            trickProperties.setProperty(xMinKey, Integer.toString(options.valueOf(xMinSpec)));
        }

        if (options.has(xMaxKey)) {
            trickProperties.setProperty(xMaxKey, Integer.toString(options.valueOf(xMaxSpec)));
        }

        if (options.has(xStepKey)) {
            trickProperties.setProperty(xStepKey, Integer.toString(options.valueOf(xStepSpec)));
        }

        if (options.has(yMinKey)) {
            trickProperties.setProperty(yMinKey, Integer.toString(options.valueOf(yMinSpec)));
        }

        if (options.has(yMaxKey)) {
            trickProperties.setProperty(yMaxKey, Integer.toString(options.valueOf(yMaxSpec)));
        }

        if (options.has(yStepKey)) {
            trickProperties.setProperty(yStepKey, Integer.toString(options.valueOf(yStepSpec)));
        }

        if (options.has(zMinKey)) {
            trickProperties.setProperty(zMinKey, Integer.toString(options.valueOf(zMinSpec)));
        }

        if (options.has(zMaxKey)) {
            trickProperties.setProperty(zMaxKey, Integer.toString(options.valueOf(zMaxSpec)));
        }

        if (options.has(zStepKey)) {
            trickProperties.setProperty(zStepKey, Integer.toString(options.valueOf(zStepSpec)));
        }

        if (options.has(pitchMinKey)) {
            trickProperties.setProperty(pitchMinKey, Integer.toString(options.valueOf(pitchMinSpec)));
        }

        if (options.has(pitchMaxKey)) {
            trickProperties.setProperty(pitchMaxKey, Integer.toString(options.valueOf(pitchMaxSpec)));
        }

        if (options.has(pitchStepKey)) {
            trickProperties.setProperty(pitchStepKey, Integer.toString(options.valueOf(pitchStepSpec)));
        }

        if (options.has(yawMinKey)) {
            trickProperties.setProperty(yawMinKey, Integer.toString(options.valueOf(yawMinSpec)));
        }

        if (options.has(yawMaxKey)) {
            trickProperties.setProperty(yawMaxKey, Integer.toString(options.valueOf(yawMaxSpec)));
        }

        if (options.has(yawStepKey)) {
            trickProperties.setProperty(yawStepKey, Integer.toString(options.valueOf(yawStepSpec)));
        }

        if (options.has(rollMinKey)) {
            trickProperties.setProperty(rollMinKey, Integer.toString(options.valueOf(rollMinSpec)));
        }

        if (options.has(rollMaxKey)) {
            trickProperties.setProperty(rollMaxKey, Integer.toString(options.valueOf(rollMaxSpec)));
        }

        if (options.has(rollStepKey)) {
            trickProperties.setProperty(rollStepKey, Integer.toString(options.valueOf(rollStepSpec)));
        }

        if (options.has(layoutKey)) {
            String layout = options.valueOf(layoutSpec);
            if (layout.equalsIgnoreCase("full")) {
                trickProperties.setProperty(layoutKey, Layout.FULL.toString());
            }
            else if (layout.equalsIgnoreCase("light")) {
                trickProperties.setProperty(layoutKey, Layout.LIGHT.toString());
            }
            else {
                System.out.println("Option ['layout'] argument must be one of ['full', 'light']");
                System.exit(0);
            }
        }

        if (options.has("fullMaximized")) {
            if (options.valueOf(fullMaximizedSpec)) {
                trickProperties.setProperty(fullStateKey, Integer.toString(JFrame.MAXIMIZED_BOTH));
            }
            else {
                trickProperties.setProperty(fullStateKey, Integer.toString(JFrame.NORMAL));
            }
        }

        if (options.has(fullXKey)) {
            trickProperties.setProperty(fullXKey, Integer.toString(options.valueOf(fullXSpec)));
        }

        if (options.has(fullYKey)) {
            trickProperties.setProperty(fullYKey, Integer.toString(options.valueOf(fullYSpec)));
        }

        if (options.has(fullWidthKey)) {
            trickProperties.setProperty(fullWidthKey, Integer.toString(options.valueOf(fullWidthSpec)));
        }

        if (options.has(fullHeightKey)) {
            trickProperties.setProperty(fullHeightKey, Integer.toString(options.valueOf(fullHeightSpec)));
        }

        if (options.has("lightMaximized")) {
            if (options.valueOf(lightMaximizedSpec)) {
                trickProperties.setProperty(lightStateKey, Integer.toString(JFrame.MAXIMIZED_BOTH));
            }
            else {
                trickProperties.setProperty(lightStateKey, Integer.toString(JFrame.NORMAL));
            }
        }

        if (options.has(lightXKey)) {
            trickProperties.setProperty(lightXKey, Integer.toString(options.valueOf(lightXSpec)));
        }

        if (options.has(lightYKey)) {
            trickProperties.setProperty(lightYKey, Integer.toString(options.valueOf(lightYSpec)));
        }

        if (options.has(lightWidthKey)) {
            trickProperties.setProperty(lightWidthKey, Integer.toString(options.valueOf(lightWidthSpec)));
        }

        if (options.has(lightHeightKey)) {
            trickProperties.setProperty(lightHeightKey, Integer.toString(options.valueOf(lightHeightSpec)));
        }
    }

    @Override
    protected void initialize(final String args[]) {
        try {
            if (System.getProperty("os.name").contains("Linux")) {
                // Linux LAFs are ugly, so use Nimbus if it's available.
                    for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                        if (info.getName().equals("Nimbus")) {
                            UIManager.setLookAndFeel(info.getClassName());
                            break;
                        }
                    }
                }
            }
        catch (Exception e) {}

        super.initialize(args);

        if (System.getProperty("os.name").contains("Mac")) {
            Application application =  Application.getApplication();
            application.setDockIconImage(resourceMap.getImageIcon("Application.icon").getImage());

            application.setAboutHandler(new AboutHandler() {
                public void handleAbout(AboutEvent e) {
                    aboutDialog.setVisible(true);
                }
            });
        }

        Layout.FULL.extendedState =
          Integer.parseInt(trickProperties.getProperty(fullStateKey, Integer.toString(JFrame.NORMAL)));

        if (trickProperties.getProperty(fullXKey) != null || trickProperties.getProperty(fullYKey) != null ||
          trickProperties.getProperty(fullWidthKey) != null || trickProperties.getProperty(fullHeightKey) != null) {
            Layout.FULL.rectangle = new Rectangle(
              Integer.parseInt(trickProperties.getProperty(fullXKey, "0")),
              Integer.parseInt(trickProperties.getProperty(fullYKey, "0")),
              Integer.parseInt(trickProperties.getProperty(fullWidthKey, "1000")),
              Integer.parseInt(trickProperties.getProperty(fullHeightKey, "600")));
        }

        Layout.LIGHT.extendedState =
          Integer.parseInt(trickProperties.getProperty(lightStateKey, Integer.toString(JFrame.NORMAL)));

        if (trickProperties.getProperty(lightXKey) != null || trickProperties.getProperty(lightYKey) != null ||
          trickProperties.getProperty(lightWidthKey) != null || trickProperties.getProperty(lightHeightKey) != null) {
            Layout.LIGHT.rectangle = new Rectangle(
              Integer.parseInt(trickProperties.getProperty(lightXKey, "0")),
              Integer.parseInt(trickProperties.getProperty(lightYKey, "0")),
              Integer.parseInt(trickProperties.getProperty(lightWidthKey, "300")),
              Integer.parseInt(trickProperties.getProperty(lightHeightKey, "600")));
        }
    }

    @Override
    protected void startup() {
        super.startup();

        // Get rid of TrickApplication's exit confirmation prompt.
        removeExitListener(exitListener);

        View view = getMainView();
        view.setComponent(createMainPanel());
        view.setMenuBar(createMenuBar());

        errorDialog = new ErrorDialog();

        settingsDialog.addPanel(new JXPanel(new BorderLayout()) {
            final JXTextField simObjectTextField = new JXTextField() {{
                setToolTipText("<html>Simulation variable name of the Input Layout<br>that this application will manipulate.</html>");
                setHorizontalAlignment(CENTER);
                setColumns(30);
                setText(simObjectName);
              }};

            final JComboBox translationOrientationComboBox = new JComboBox(Translation.values());
            final JComboBox rotationOrientationComboBox = new JComboBox(Rotation.values());

            final JCheckBox xCheckBox = new JCheckBox("Invert X", xSlider.slider.getInverted()) {{
                setMnemonic(KeyEvent.VK_X);
            }};
            final JCheckBox yCheckBox = new JCheckBox("Invert Y", ySlider.slider.getInverted()) {{
                setMnemonic(KeyEvent.VK_Y);
            }};
            final JCheckBox zCheckBox = new JCheckBox("Invert Z", zSlider.slider.getInverted()) {{
                setMnemonic(KeyEvent.VK_Z);
            }};
            final JCheckBox pitchCheckBox = new JCheckBox("Invert Pitch", pitchSlider.slider.getInverted()) {{
                setMnemonic(KeyEvent.VK_P);
            }};
            final JCheckBox yawCheckBox = new JCheckBox("Invert Yaw", yawSlider.slider.getInverted()) {{
                setMnemonic(KeyEvent.VK_W);
            }};
            final JCheckBox rollCheckBox = new JCheckBox("Invert Roll", rollSlider.slider.getInverted()) {{
                setMnemonic(KeyEvent.VK_R);
                setDisplayedMnemonicIndex(7);
            }};

            // focus the next component when the Enter key is pressed
            final ActionListener actionListener = new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    KeyboardFocusManager.getCurrentKeyboardFocusManager().focusNextComponent();
                }
            };

            // select all when focus is gained
            final FocusAdapter focusAdapter = new FocusAdapter() {
                @Override
                public void focusGained(final FocusEvent event) {
                    // JXFormattedTextField already manipulates the selection when it gains focus, so we must ensure the
                    // selectAll call is executed after it is done, or the selection won't hold.
                    SwingUtilities.invokeLater(new Runnable() {
                        public void run() {
                            ((JXFormattedTextField)event.getSource()).selectAll();
                        }
                    });
                }
            };

            // formatted text field with a minimum value, fixed size, and allowing only integers
            class IntegerTextField extends JXFormattedTextField {

                public IntegerTextField(int minimum) {
                    this();
                    ((NumberFormatter)getFormatter()).setMinimum(minimum);
                }

                public IntegerTextField() {
                    setHorizontalAlignment(RIGHT);
                    setText("-00000");
                    setPreferredSize(getPreferredSize());
                    addActionListener(actionListener);
                    addFocusListener(focusAdapter);
                    setFormatterFactory(new DefaultFormatterFactory() {{
                        setDefaultFormatter(new NumberFormatter() {{
                            setValueClass(Integer.class);
                            ((NumberFormat)getFormat()).setGroupingUsed(false);
                        }});
                    }});
                }

                public int getIntValue() {
                    return ((Integer)getValue()).intValue();
                }

            };

            final IntegerTextField xMinTextField = new IntegerTextField();
            final IntegerTextField xMaxTextField = new IntegerTextField();
            final IntegerTextField xStepTextField = new IntegerTextField(1);

            final IntegerTextField yMinTextField = new IntegerTextField();
            final IntegerTextField yMaxTextField = new IntegerTextField();
            final IntegerTextField yStepTextField = new IntegerTextField(1);

            final IntegerTextField zMinTextField = new IntegerTextField();
            final IntegerTextField zMaxTextField = new IntegerTextField();
            final IntegerTextField zStepTextField = new IntegerTextField(1);

            final IntegerTextField pitchMinTextField = new IntegerTextField();
            final IntegerTextField pitchMaxTextField = new IntegerTextField();
            final IntegerTextField pitchStepTextField = new IntegerTextField(1);

            final IntegerTextField yawMinTextField = new IntegerTextField();
            final IntegerTextField yawMaxTextField = new IntegerTextField();
            final IntegerTextField yawStepTextField = new IntegerTextField(1);

            final IntegerTextField rollMinTextField = new IntegerTextField();
            final IntegerTextField rollMaxTextField = new IntegerTextField();
            final IntegerTextField rollStepTextField = new IntegerTextField(1);

            JCheckBox toggleRateHoldCheckBox = new JCheckBox("Toggle Rate Hold") {
                {
                setToolTipText("<html>Toggles the behavior of the Rate Hold button<br>" +
                  "between Toggle and Click-and-Hold.</html>");
                setMnemonic(KeyEvent.VK_H);
                setHorizontalAlignment(SwingConstants.CENTER);
                }

                @Override
                public float getAlignmentX() {
                    return CENTER_ALIGNMENT;
                }
            };

            JCheckBox stickyTriggerCheckBox = new JCheckBox("Sticky Trigger") {
                {
                setToolTipText("<html>Toggles the behavior of the Trigger buttons<br>" +
                  "between Sticky and  Click-and-Hold.</html>");
                setMnemonic(KeyEvent.VK_T);
                setDisplayedMnemonicIndex(7);
                setHorizontalAlignment(SwingConstants.CENTER);
                }

                @Override
                public float getAlignmentX() {
                    return CENTER_ALIGNMENT;
                }
            };

            {
                add(new JXPanel() {{
                    setBorder(new TitledBorder("Virtual Layout Path") {{
                        setTitleJustification(CENTER);
                    }});
                    add(simObjectTextField);
                }}, BorderLayout.NORTH);

                add(new Box(BoxLayout.Y_AXIS) {{
                    add(new JXPanel(new GridLayout(1, 2)) {{
                        final GridBagConstraints constraints = new GridBagConstraints();

                        add(new JXPanel(new GridBagLayout()) {{
                            setBorder(new TitledBorder("Orientation") {{
                                setTitleJustification(CENTER);
                            }});
                            constraints.gridx = 1;
                            add(translationOrientationComboBox, constraints);
                            add(rotationOrientationComboBox, constraints);
                            constraints.anchor = GridBagConstraints.WEST;
                            constraints.insets.right = 5;
                            constraints.gridx = 0;
                            constraints.gridy = 0;
                            add(new JXLabel("Translation:"), constraints);
                            constraints.gridy = GridBagConstraints.RELATIVE;
                            add(new JXLabel("Rotation:"), constraints);
                            constraints.insets.right = 0;
                            constraints.gridwidth = GridBagConstraints.REMAINDER;
                            constraints.anchor = GridBagConstraints.CENTER;
                            add(new JXPanel(new GridLayout(6, 1)) {{
                                add(xCheckBox);
                                add(yCheckBox);
                                add(zCheckBox);
                                add(pitchCheckBox);
                                add(yawCheckBox);
                                add(rollCheckBox);
                            }}, constraints);
                        }});

                        add(new JXPanel(new GridBagLayout()) {{
                            setBorder(new TitledBorder("Bounds") {{
                                setTitleJustification(CENTER);
                            }});
                            constraints.gridwidth = 1;
                            constraints.gridx = 1;
                            constraints.gridy = 0;
                            add(new JXLabel("Min") {{
                                setHorizontalAlignment(JXLabel.CENTER);
                                setToolTipText("<html>The minimum value that<br>the slider can take.</html>");
                            }}, constraints);
                            constraints.gridy = GridBagConstraints.RELATIVE;
                            add(xMinTextField, constraints);
                            add(yMinTextField, constraints);
                            add(zMinTextField, constraints);
                            add(pitchMinTextField, constraints);
                            add(yawMinTextField, constraints);
                            add(rollMinTextField, constraints);

                            constraints.gridx = 2;
                            constraints.gridy = 0;
                            add(new JXLabel("Max") {{
                                setHorizontalAlignment(JXLabel.CENTER);
                                setToolTipText("<html>The maximum value that<br>the slider can take.</html>");
                            }}, constraints);
                            constraints.gridy = GridBagConstraints.RELATIVE;
                            add(xMaxTextField, constraints);
                            add(yMaxTextField, constraints);
                            add(zMaxTextField, constraints);
                            add(pitchMaxTextField, constraints);
                            add(yawMaxTextField, constraints);
                            add(rollMaxTextField, constraints);

                            constraints.gridx = 3;
                            constraints.gridy = 0;
                            add(new JXLabel("Step") {{
                                setHorizontalAlignment(JXLabel.CENTER);
                                setToolTipText("<html>The step size by which the slider is<br>" + 
                                  "changed when clicking a button.</html>");
                            }}, constraints);
                            constraints.gridy = GridBagConstraints.RELATIVE;
                            add(xStepTextField, constraints);
                            add(yStepTextField, constraints);
                            add(zStepTextField, constraints);
                            add(pitchStepTextField, constraints);
                            add(yawStepTextField, constraints);
                            add(rollStepTextField, constraints);

                            constraints.gridx = 0;
                            constraints.gridy = 1;
                            constraints.insets.right = 5;
                            add(new JXLabel("X"), constraints);
                            constraints.gridy = GridBagConstraints.RELATIVE;
                            add(new JXLabel("Y"), constraints);
                            add(new JXLabel("Z"), constraints);
                            add(new JXLabel("Pitch"), constraints);
                            add(new JXLabel("Yaw"), constraints);
                            add(new JXLabel("Roll"), constraints);
                        }});
                    }});

                    /*add(new JXPanel(new GridLayout(1, 2)) {{
                        setBorder(new TitledBorder("Button Behavior") {{
                            setTitleJustification(CENTER);
                        }});
                        add(toggleRateHoldCheckBox);
                        add(stickyTriggerCheckBox);
                    }});*/
                }}, BorderLayout.CENTER);

                settingsDialog.addBecomingVisibleListener(new BecomingVisibleListener() {
                    @Override
                    public void becomingVisible() {
                        simObjectTextField.setText(simObjectName);

                        translationOrientationComboBox.setSelectedItem(translationOrientation);
                        rotationOrientationComboBox.setSelectedItem(rotationOrientation);

                        xCheckBox.setSelected(xSlider.slider.getInverted());
                        xMinTextField.setValue(new Integer(xSlider.slider.getMinimum()));
                        xMaxTextField.setValue(new Integer(xSlider.slider.getMaximum()));
                        xStepTextField.setValue(new Integer(xSlider.step));

                        yCheckBox.setSelected(ySlider.slider.getInverted());
                        yMinTextField.setValue(new Integer(ySlider.slider.getMinimum()));
                        yMaxTextField.setValue(new Integer(ySlider.slider.getMaximum()));
                        yStepTextField.setValue(new Integer(ySlider.step));

                        zCheckBox.setSelected(zSlider.slider.getInverted());
                        zMinTextField.setValue(new Integer(zSlider.slider.getMinimum()));
                        zMaxTextField.setValue(new Integer(zSlider.slider.getMaximum()));
                        zStepTextField.setValue(new Integer(zSlider.step));

                        pitchCheckBox.setSelected(pitchSlider.slider.getInverted());
                        pitchMinTextField.setValue(new Integer(pitchSlider.slider.getMinimum()));
                        pitchMaxTextField.setValue(new Integer(pitchSlider.slider.getMaximum()));
                        pitchStepTextField.setValue(new Integer(pitchSlider.step));

                        yawCheckBox.setSelected(yawSlider.slider.getInverted());
                        yawMinTextField.setValue(new Integer(yawSlider.slider.getMinimum()));
                        yawMaxTextField.setValue(new Integer(yawSlider.slider.getMaximum()));
                        yawStepTextField.setValue(new Integer(yawSlider.step));

                        rollCheckBox.setSelected(rollSlider.slider.getInverted());
                        rollMinTextField.setValue(new Integer(rollSlider.slider.getMinimum()));
                        rollMaxTextField.setValue(new Integer(rollSlider.slider.getMaximum()));
                        rollStepTextField.setValue(new Integer(rollSlider.step));

                        toggleRateHoldCheckBox.setSelected(!rateHoldButtonListener.isEnabled());
                        stickyTriggerCheckBox.setSelected(!triggerUpButtonListener.isEnabled());
                    }
                });

                settingsDialog.addCommitChangesListener(new CommitChangesListener() {
                    @Override
                    public void commitChanges() {
                        xSlider.step = xStepTextField.getIntValue();
                        xSlider.slider.setInverted(xCheckBox.isSelected());
                        xSlider.setRange(xMinTextField.getIntValue(), xMaxTextField.getIntValue());

                        ySlider.step = yStepTextField.getIntValue();
                        ySlider.slider.setInverted(yCheckBox.isSelected());
                        ySlider.setRange(yMinTextField.getIntValue(), yMaxTextField.getIntValue());

                        zSlider.step = zStepTextField.getIntValue();
                        zSlider.slider.setInverted(zCheckBox.isSelected());
                        zSlider.setRange(zMinTextField.getIntValue(), zMaxTextField.getIntValue());

                        pitchSlider.step = pitchStepTextField.getIntValue();
                        pitchSlider.slider.setInverted(pitchCheckBox.isSelected());
                        pitchSlider.setRange(pitchMinTextField.getIntValue(), pitchMaxTextField.getIntValue());

                        yawSlider.step = yawStepTextField.getIntValue();
                        yawSlider.slider.setInverted(yawCheckBox.isSelected());
                        yawSlider.setRange(yawMinTextField.getIntValue(), yawMaxTextField.getIntValue());

                        rollSlider.step = rollStepTextField.getIntValue();
                        rollSlider.slider.setInverted(rollCheckBox.isSelected());
                        rollSlider.setRange(rollMinTextField.getIntValue(), rollMaxTextField.getIntValue());

                        setTranslationOrientation((Translation)translationOrientationComboBox.getSelectedItem());
                        setRotationOrientation((Rotation)rotationOrientationComboBox.getSelectedItem());

                        rateHoldButtonListener.setEnabled(!toggleRateHoldCheckBox.isSelected());
                        // If toggling is disabled, set to the non-pressed state.
                        if (!toggleRateHoldCheckBox.isSelected()) {
                            rateHoldToggleButton.setSelected(false);
                        }

                        triggerUpButtonListener.setEnabled(!stickyTriggerCheckBox.isSelected());
                        triggerDownButtonListener.setEnabled(!stickyTriggerCheckBox.isSelected());
                        // If sticking is disabled, set to the neutral state.
                        if (!stickyTriggerCheckBox.isSelected()) {
                            setSelection(triggerRadioGroup, 1);
                        }

                        // If the sim object name was changed, we need to send the full state to the sim
                        // to ensure the sim matches the GUI.
                        String name = simObjectTextField.getText().trim();
                        if (!name.equals(simObjectName)) {
                            setSimObjectName(name);
                            sendFullState();
                        }
                        simObjectTextField.setText(simObjectName);
                    }
                });

                /*if (System.getProperty("os.name").contains("Mac")) {
                    Application.getApplication().setPreferencesHandler(new PreferencesHandler() {
                        public void handlePreferences(PreferencesEvent e) {
                            setVisible(true);
                        }
                    });
                }*/

            }

        });

        aboutDialog = new JDialog(getMainFrame(), "About " + resourceMap.getString("Application.title"), true) {

            {
            setContentPane(new JXPanel(new GridBagLayout()) {{
                setBorder(new EmptyBorder(10, 10, 10, 10));
            }});
            GridBagConstraints constraints = new GridBagConstraints() {{
                gridx = 0;
            }};
            add(new JXLabel(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/virtualHandController.png"))) {{
                setBorder(new EmptyBorder(5, 0, 5, 0));
            }}, constraints);
            add(new JXLabel(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/handControllers.png"))) {{
                setBorder(new EmptyBorder(5, 0, 5, 0));
            }}, constraints);
            add(new JXLabel("Derek Bankieris") {{
                setFont(new Font(getFont().getFontName(), Font.BOLD, getFont().getSize() + 5));
            }}, constraints);
            add(new JXLabel("<html><b><a href=\"inactive\">derek.r.bankieris@nasa.gov</a></b></html>") {{
                addMouseListener(new MouseAdapter() {
                    public void mouseClicked(MouseEvent e) {
                        try {
                            Desktop.getDesktop().mail(new URI("mailto", "derek.r.bankieris", null));
                        }
                        catch (Exception ex) {}
                    }
                });
            }}, constraints);
            pack();
            }

            public void setVisible(boolean visible) {
                if (visible) {
                    setLocationRelativeTo(getMainFrame());
                }
                super.setVisible(visible);
            }

        };

        show(view);

        // SingleFrameApplication's session state restoring code (which includes geometry) is run in show(), so we must
        // configure our layout after calling show().
        setSimObjectName(trickProperties.getProperty(simObjectNameKey, simObjectName));
        configureLayout(Layout.valueOf(trickProperties.getProperty(layoutKey,
          Layout.FULL.toString())));
    }

    @Override
    protected void shutdown() {
        trickProperties.setProperty(layoutKey, layout.toString());

        layout.extendedState = getMainFrame().getExtendedState();
        if ((layout.extendedState & JFrame.NORMAL) == JFrame.NORMAL) {
            layout.rectangle = getMainFrame().getBounds();
        }

        trickProperties.setProperty(fullStateKey, Integer.toString(Layout.FULL.extendedState));
        if (Layout.FULL.rectangle != null) {
            trickProperties.setProperty(fullXKey, Integer.toString(Layout.FULL.rectangle.x));
            trickProperties.setProperty(fullYKey, Integer.toString(Layout.FULL.rectangle.y));
            trickProperties.setProperty(fullWidthKey, Integer.toString(Layout.FULL.rectangle.width));
            trickProperties.setProperty(fullHeightKey, Integer.toString(Layout.FULL.rectangle.height));
        }

        trickProperties.setProperty(lightStateKey, Integer.toString(Layout.LIGHT.extendedState));
        if (Layout.LIGHT.rectangle != null) {
            trickProperties.setProperty(lightXKey, Integer.toString(Layout.LIGHT.rectangle.x));
            trickProperties.setProperty(lightYKey, Integer.toString(Layout.LIGHT.rectangle.y));
            trickProperties.setProperty(lightWidthKey, Integer.toString(Layout.LIGHT.rectangle.width));
            trickProperties.setProperty(lightHeightKey, Integer.toString(Layout.LIGHT.rectangle.height));
        }

        trickProperties.setProperty(simObjectNameKey, simObjectName);

        trickProperties.setProperty(translationOrientationKey, translationOrientation.toString());
        trickProperties.setProperty(rotationOrientationKey, rotationOrientation.toString());

        trickProperties.setProperty(invertXKey, Boolean.toString(xSlider.slider.getInverted()));
        trickProperties.setProperty(xMinKey, Integer.toString(xSlider.slider.getMinimum()));
        trickProperties.setProperty(xMaxKey, Integer.toString(xSlider.slider.getMaximum()));
        trickProperties.setProperty(xStepKey, Integer.toString(xSlider.step));

        trickProperties.setProperty(invertYKey, Boolean.toString(ySlider.slider.getInverted()));
        trickProperties.setProperty(yMinKey, Integer.toString(ySlider.slider.getMinimum()));
        trickProperties.setProperty(yMaxKey, Integer.toString(ySlider.slider.getMaximum()));
        trickProperties.setProperty(yStepKey, Integer.toString(ySlider.step));

        trickProperties.setProperty(invertZKey, Boolean.toString(zSlider.slider.getInverted()));
        trickProperties.setProperty(zMinKey, Integer.toString(zSlider.slider.getMinimum()));
        trickProperties.setProperty(zMaxKey, Integer.toString(zSlider.slider.getMaximum()));
        trickProperties.setProperty(zStepKey, Integer.toString(zSlider.step));

        trickProperties.setProperty(invertPitchKey, Boolean.toString(pitchSlider.slider.getInverted()));
        trickProperties.setProperty(pitchMinKey, Integer.toString(pitchSlider.slider.getMinimum()));
        trickProperties.setProperty(pitchMaxKey, Integer.toString(pitchSlider.slider.getMaximum()));
        trickProperties.setProperty(pitchStepKey, Integer.toString(pitchSlider.step));

        trickProperties.setProperty(invertYawKey, Boolean.toString(yawSlider.slider.getInverted()));
        trickProperties.setProperty(yawMinKey, Integer.toString(yawSlider.slider.getMinimum()));
        trickProperties.setProperty(yawMaxKey, Integer.toString(yawSlider.slider.getMaximum()));
        trickProperties.setProperty(yawStepKey, Integer.toString(yawSlider.step));

        trickProperties.setProperty(invertRollKey, Boolean.toString(rollSlider.slider.getInverted()));
        trickProperties.setProperty(rollMinKey, Integer.toString(rollSlider.slider.getMinimum()));
        trickProperties.setProperty(rollMaxKey, Integer.toString(rollSlider.slider.getMaximum()));
        trickProperties.setProperty(rollStepKey, Integer.toString(rollSlider.step));

        /*trickProperties.setProperty(grannularityKey, Integer.toString(getSelectedIndex(grannularityRadioGroup)));
        trickProperties.setProperty(grannularityVisibleKey, Boolean.toString(grannularityRadioGroup.isVisible()));

        trickProperties.setProperty(toggleRateHoldKey, Boolean.toString(!rateHoldButtonListener.isEnabled()));
        trickProperties.setProperty(rateHoldKey, Boolean.toString(rateHoldToggleButton.isSelected()));
        trickProperties.setProperty(rateHoldVisibleKey, Boolean.toString(rateHoldToggleButton.isVisible()));

        trickProperties.setProperty(stickyTriggerKey, Boolean.toString(!triggerUpButtonListener.isEnabled()));
        trickProperties.setProperty(triggerKey, Integer.toString(getSelectedIndex(triggerRadioGroup)));
        trickProperties.setProperty(triggerVisibleKey, Boolean.toString(triggerRadioGroup.isVisible()));*/

        super.shutdown();
    }

    @Override
    protected JMenuBar createMenuBar() {
        // radio button that sets the layout when clicked
        class ViewRadioButtonMenuItem extends JRadioButtonMenuItem {
            public ViewRadioButtonMenuItem(String text, int mnemonic, final Layout layout) {
                super(text);
                setMnemonic(mnemonic);
                addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent event) {
                        configureLayout(layout);
                    }
                });
            }
        };

        // check box that sets the target component's visibility when clicked
        class ViewCheckBoxMenuItem extends JCheckBoxMenuItem {
            public ViewCheckBoxMenuItem(String text, int mnemonic, final JComponent targetComponent) {
                super(text);
                setMnemonic(mnemonic);
                setSelected(targetComponent.isVisible());
                addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent event) {
                        targetComponent.setVisible(isSelected());
                    }
                });
            }
        };

        JMenuBar menuBar = super.createMenuBar();

        if (!System.getProperty("os.name").contains("Mac")) {
            menuBar.add(new JMenu("Help") {{

                add(new JMenuItem(new AbstractAction() {
                    {
                    putValue(NAME, "About");
                    putValue(SHORT_DESCRIPTION, "Display information about this application.");
                    putValue(MNEMONIC_KEY, KeyEvent.VK_A);
                    }
                    public void actionPerformed(ActionEvent e) {
                        aboutDialog.setVisible(true);
                    }
                }));
            }}, 1);
        }

        menuBar.add(new JMenu("View") {{
            setMnemonic(KeyEvent.VK_V);

            final ViewRadioButtonMenuItem fullView =
              new ViewRadioButtonMenuItem("Full", KeyEvent.VK_F, Layout.FULL) {{
                  setSelected(Layout.valueOf(trickProperties.getProperty(layoutKey,
                    Layout.FULL.toString())) == Layout.FULL);
              }};

            final ViewRadioButtonMenuItem lightView =
              new ViewRadioButtonMenuItem("Light", KeyEvent.VK_L, Layout.LIGHT) {{
                  setSelected(!fullView.isSelected());
              }};

            new ButtonGroup() {{
                add(fullView);
                add(lightView);
            }};

            add(fullView);
            add(lightView);
            /*add(new JSeparator());
            add(new ViewCheckBoxMenuItem("Grannularity", KeyEvent.VK_G, grannularityRadioGroup));
            add(new ViewCheckBoxMenuItem("Rate Hold", KeyEvent.VK_R, rateHoldToggleButton));
            add(new ViewCheckBoxMenuItem("Trigger", KeyEvent.VK_T, triggerRadioGroup));*/
        }}, 1);

        return menuBar;
    }

    @Override
    protected JComponent createMainPanel() {
        translationPanel = new ThreeDOFPanel("Z", "Y", "X") {{

            setBorder(new TitledBorder("Translation") {{
                setTitleJustification(CENTER);
            }});

            buttonGrid.northWestButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/northWestArrow.png")));

            buttonGrid.northButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/northArrow.png")));

            buttonGrid.northEastButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/northEastArrow.png")));

            buttonGrid.westButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/westArrow.png")));

            buttonGrid.centerLeftButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/inArrow.png")));

            buttonGrid.centerRightButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/outArrow.png")));

            buttonGrid.eastButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/eastArrow.png")));

            buttonGrid.southWestButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/southWestArrow.png")));

            buttonGrid.southButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/southArrow.png")));

            buttonGrid.southEastButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/southEastArrow.png")));

            buttonGrid.northButton.setMnemonic(KeyEvent.VK_W);
            buttonGrid.eastButton.setMnemonic(KeyEvent.VK_D);
            buttonGrid.southButton.setMnemonic(KeyEvent.VK_S);
            buttonGrid.westButton.setMnemonic(KeyEvent.VK_A);
            buttonGrid.centerLeftButton.setMnemonic(KeyEvent.VK_Q);
            buttonGrid.centerRightButton.setMnemonic(KeyEvent.VK_E);

            xSlider = firstSlider;
            ySlider = secondSlider;
            zSlider = thirdSlider;
        }};

        rotationPanel = new ThreeDOFPanel("Pitch", "Yaw", "Roll") {{

            setBorder(new TitledBorder("Rotation") {{
                setTitleJustification(CENTER);

            }});

            buttonGrid.northWestButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/northWestInArrow.png")));

            buttonGrid.northButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/northInArrow.png")));

            buttonGrid.northEastButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/northEastInArrow.png")));

            buttonGrid.eastButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/eastInArrow.png")));

            buttonGrid.centerLeftButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/northWestCurvedArrow.png")));

            buttonGrid.centerRightButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/northEastCurvedArrow.png")));

            buttonGrid.westButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/westInArrow.png")));

            buttonGrid.southWestButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/southWestInArrow.png")));

            buttonGrid.southButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/southInArrow.png")));

            buttonGrid.southEastButton.setImageIcon(
              new ImageIcon(VirtualHandControllerMain.class.getResource("resources/southEastInArrow.png")));

            buttonGrid.northButton.setMnemonic(KeyEvent.VK_P);
            buttonGrid.eastButton.setMnemonic(KeyEvent.VK_QUOTE);
            buttonGrid.southButton.setMnemonic(KeyEvent.VK_SEMICOLON);
            buttonGrid.westButton.setMnemonic(KeyEvent.VK_L);
            buttonGrid.centerLeftButton.setMnemonic(KeyEvent.VK_O);
            buttonGrid.centerRightButton.setMnemonic(KeyEvent.VK_OPEN_BRACKET);

            pitchSlider = firstSlider;
            yawSlider = secondSlider;
            rollSlider = thirdSlider;
        }};

        setTranslationOrientation(Enum.valueOf(Translation.class,
          trickProperties.getProperty(translationOrientationKey, Translation.XYZ.toString())));

        setRotationOrientation(Enum.valueOf(Rotation.class,
          trickProperties.getProperty(rotationOrientationKey, Rotation.RPY.toString())));

        xSlider.slider.setInverted(Boolean.parseBoolean(
          trickProperties.getProperty(invertXKey, Boolean.toString(false))));
        xSlider.step = Integer.parseInt(trickProperties.getProperty(xStepKey, "10"));
        int xMin = Integer.parseInt(trickProperties.getProperty(xMinKey, "-100"));
        int xMax = Integer.parseInt(trickProperties.getProperty(xMaxKey, "100"));
        xSlider.setRange(xMin, xMax);
        xSlider.slider.setValue(0);

        ySlider.slider.setInverted(Boolean.parseBoolean(
          trickProperties.getProperty(invertYKey, Boolean.toString(false))));
        ySlider.step = Integer.parseInt(trickProperties.getProperty(yStepKey, "10"));
        int yMin = Integer.parseInt(trickProperties.getProperty(yMinKey, "-100"));
        int yMax = Integer.parseInt(trickProperties.getProperty(yMaxKey, "100"));
        ySlider.setRange(yMin, yMax);
        ySlider.slider.setValue(0);

        zSlider.slider.setInverted(Boolean.parseBoolean(
          trickProperties.getProperty(invertZKey, Boolean.toString(false))));
        zSlider.step = Integer.parseInt(trickProperties.getProperty(zStepKey, "10"));
        int zMin = Integer.parseInt(trickProperties.getProperty(zMinKey, "-100"));
        int zMax = Integer.parseInt(trickProperties.getProperty(zMaxKey, "100"));
        zSlider.setRange(zMin, zMax);
        zSlider.slider.setValue(0);

        pitchSlider.slider.setInverted(Boolean.parseBoolean(
          trickProperties.getProperty(invertPitchKey, Boolean.toString(false))));
        pitchSlider.step = Integer.parseInt(trickProperties.getProperty(pitchStepKey, "10"));
        int pitchMin = Integer.parseInt(trickProperties.getProperty(pitchMinKey, "-100"));
        int pitchMax = Integer.parseInt(trickProperties.getProperty(pitchMaxKey, "100"));
        pitchSlider.setRange(pitchMin, pitchMax);
        pitchSlider.slider.setValue(0);

        yawSlider.slider.setInverted(Boolean.parseBoolean(
          trickProperties.getProperty(invertYawKey, Boolean.toString(false))));
        yawSlider.step = Integer.parseInt(trickProperties.getProperty(yawStepKey, "10"));
        int yawMin = Integer.parseInt(trickProperties.getProperty(yawMinKey, "-100"));
        int yawMax = Integer.parseInt(trickProperties.getProperty(yawMaxKey, "100"));
        yawSlider.setRange(yawMin, yawMax);
        yawSlider.slider.setValue(0);

        rollSlider.slider.setInverted(Boolean.parseBoolean(
          trickProperties.getProperty(invertRollKey, Boolean.toString(false))));
        rollSlider.step = Integer.parseInt(trickProperties.getProperty(rollStepKey, "10"));
        int rollMin = Integer.parseInt(trickProperties.getProperty(rollMinKey, "-100"));
        int rollMax = Integer.parseInt(trickProperties.getProperty(rollMaxKey, "100"));
        rollSlider.setRange(rollMin, rollMax);
        rollSlider.slider.setValue(0);

        // send the sliders' values to the Variable Server when they change
        final ChangeListener changeListener = new ChangeListener() {
            public void stateChanged(ChangeEvent event) {
                sendSliderValue((JSlider)event.getSource());
            }
        };

        xSlider.slider.addChangeListener(changeListener);
        ySlider.slider.addChangeListener(changeListener);
        zSlider.slider.addChangeListener(changeListener);
        pitchSlider.slider.addChangeListener(changeListener);
        yawSlider.slider.addChangeListener(changeListener);
        rollSlider.slider.addChangeListener(changeListener);

        rateHoldToggleButton = new JToggleButton("Rate Hold") {{
            setToolTipText("<html>When active, the simulation will<br>maintain its current rates.</html>");
            setMnemonic(KeyEvent.VK_H);
            setSelected(Boolean.parseBoolean(trickProperties.getProperty(rateHoldKey, Boolean.toString(false))));
            setVisible(Boolean.parseBoolean(trickProperties.getProperty(rateHoldVisibleKey, Boolean.toString(true))));

            // sends the rate hold command to the Variable Server when clicked
            addItemListener(new ItemListener() {
                public void itemStateChanged(ItemEvent e) {
                    sendRateHold();
                }
            });

            // Since this is a toggle button, it will stay depressed when clicked. This listener will release it if toggling
            // is disabled.
            addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    if (rateHoldButtonListener.isEnabled()) {
                        setSelected(false);
                    }
                }
            });

            // In click-and-hold mode, we must depress the button whenever the mouse is pressed over it.
            rateHoldButtonListener = new ButtonListener(this) {
                {
                setEnabled(!Boolean.parseBoolean(trickProperties.getProperty(toggleRateHoldKey, Boolean.toString(true))));
                }
                void activeChanged(boolean active) {
                    setSelected(active);
                }
            };
        }};

        grannularityRadioGroup = new JXRadioGroup<JRadioButton>() {

            final JRadioButton coarseRadioButton = new JRadioButton("Coarse") {{
                setMnemonic(KeyEvent.VK_R);
            }};

            final JRadioButton fineRadioButton = new JRadioButton("Fine") {{
                setMnemonic(KeyEvent.VK_I);
            }};

            final GridBagConstraints constraints = new GridBagConstraints() {{
                gridx = 0;
                fill = BOTH;
                weightx = 1;
                weighty = 1;
            }};

            {
            setBorder(new TitledBorder("Grannularity") {{
                setTitleJustification(CENTER);
            }});

            setLayout(new GridBagLayout());
            add(coarseRadioButton);
            add(fineRadioButton);

            setSelection(this, Integer.parseInt(trickProperties.getProperty(grannularityKey, "0")));

            setVisible(Boolean.parseBoolean(trickProperties.getProperty(grannularityVisibleKey, Boolean.toString(true))));

            // sends the grannularity command to the Variable Server when changed
            addActionListener(new ActionListener() {
                JRadioButton previousSelection = getSelectedValue();
                public void actionPerformed(ActionEvent event) {
                    if (getSelectedValue() != previousSelection) {
                        previousSelection = getSelectedValue();
                        sendGrannularity();
                    }
                }
            });
            }

            public void add(JRadioButton radioButton) {
                super.add(radioButton);
                remove(radioButton);
                add(radioButton, constraints);
            }
        };

        triggerRadioGroup = new JXRadioGroup<JRadioButton>() {

            final JRadioButton triggerNeutralRadioButton = new JRadioButton("Neutral") {{
                setMnemonic(KeyEvent.VK_T);
            }};

            final JRadioButton triggerUpRadioButton = new JRadioButton("Up") {{
                setMnemonic(KeyEvent.VK_U);

                // Radio buttons stay selected when clicked by default. This listener will "release" the trigger if sticking
                // is disabled.
                addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        if (triggerUpButtonListener.isEnabled()) {
                            triggerNeutralRadioButton.setSelected(true);
                        }
                    }
                });

                // In click-and-hold mode, we must select the radio button whenever the mouse is pressed over it.
                triggerUpButtonListener = new ButtonListener(this) {
                    {
                    setEnabled(!Boolean.parseBoolean(trickProperties.getProperty(
                      stickyTriggerKey, Boolean.toString(false))));
                    }
                    void activeChanged(boolean active) {
                        if (active) {
                            setSelected(true);
                        }
                        else {
                            triggerNeutralRadioButton.setSelected(true);
                        }
                    }
                };
            }};

            final JRadioButton triggerDownRadioButton = new JRadioButton("Down") {{
                setMnemonic(KeyEvent.VK_N);

                // Radio buttons stay selected when clicked by default. This listener will "release" the trigger if sticking
                // is disabled.
                addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        if (triggerDownButtonListener.isEnabled()) {
                            triggerNeutralRadioButton.setSelected(true);
                        }
                    }
                });

                // In click-and-hold mode, we must select the radio button whenever the mouse is pressed over it.
                triggerDownButtonListener = new ButtonListener(this) {
                    {
                    setEnabled(!Boolean.parseBoolean(trickProperties.getProperty(
                      stickyTriggerKey, Boolean.toString(false))));
                    }
                    void activeChanged(boolean active) {
                        if (active) {
                            setSelected(true);
                        }
                        else {
                            triggerNeutralRadioButton.setSelected(true);
                        }
                    }
                };
            }};

            {
            setLayoutAxis(BoxLayout.Y_AXIS);
            setBorder(new TitledBorder("Trigger") {{
                setTitleJustification(CENTER);
            }});

            add(triggerUpRadioButton);
            add(triggerNeutralRadioButton);
            add(triggerDownRadioButton);

            setSelection(this, Integer.parseInt(trickProperties.getProperty(triggerKey, "1")));

            setVisible(Boolean.parseBoolean(trickProperties.getProperty(triggerVisibleKey, Boolean.toString(true))));

            // Send the trigger command to the Variable Server when changed.
            ItemListener itemListener = new ItemListener() {
                public void itemStateChanged(ItemEvent event) {
                    if (event.getStateChange() == ItemEvent.SELECTED) {
                        sendTrigger();
                    }
                }
            };

            triggerUpRadioButton.addItemListener(itemListener);
            triggerNeutralRadioButton.addItemListener(itemListener);
            triggerDownRadioButton.addItemListener(itemListener);
            }

        };


        mainPanel = new JXPanel(new BorderLayout());
        return mainPanel;
    }

    /**
     * configures the layout
     *
     * @param layout the configuration
     */
    void configureLayout(final Layout layout) {
        if (this.layout != layout) {
            mainPanel.removeAll();
            translationPanel.configureLayout(layout);
            rotationPanel.configureLayout(layout);

            switch (layout) {

                case FULL:
                    mainPanel.add(new JXPanel(new GridLayout(1, 2)) {{
                        add(translationPanel);
                        add(rotationPanel);
                    }}, BorderLayout.CENTER);
                    break;

                case LIGHT:
                    mainPanel.add(new JXPanel(new GridLayout(2, 1)) {{
                        add(translationPanel);
                        add(rotationPanel);
                    }}, BorderLayout.CENTER);
                    break;
            }

            /*mainPanel.add(new JXPanel(new GridBagLayout()) {{
                GridBagConstraints constraints = new GridBagConstraints() {{
                    fill = VERTICAL;
                    weighty = 1;
                }};
                add(grannularityRadioGroup, constraints);
                add(rateHoldToggleButton, constraints);
                add(triggerRadioGroup, constraints);
            }}, BorderLayout.SOUTH);*/

            if (this.layout != null) {
                saveLayout();
            }

            // saveLayout() executes code via SwingUtilities.invokeLater(), so we must do so here as well to ensure this code
            // executes after saveLayout() completes.
            SwingUtilities.invokeLater(new java.lang.Runnable() {
                public void run() {
                    VirtualHandControllerMain.this.layout = layout;
                    if (layout.rectangle != null) {
                        getMainFrame().setBounds(layout.rectangle);
                        getMainFrame().setExtendedState(layout.extendedState);
                    }
                    else {
                        getMainFrame().pack();
                    }
                    mainPanel.revalidate();
                }
            });
        }
    }

    /**
     * saves the layout. When the maximize button is cliked, the window saves the bounds to return to when unmaximized.
     * Since we want to save an unmaximized bounds for each layout, whenever the user changes the layout, we must first
     * unmaximize the window, save the bounds, set the new layout, restore its bounds, and restore its maximized
     * state. JFrame.setExtendedState() ultimately ends up making an asynchronous call to the OS (I think). So to
     * maximize our chance of recording the unmaximized bounds, add the saving logic to the end of the EDT queue.
     */
    void saveLayout() {
        layout.extendedState = getMainFrame().getExtendedState();
        getMainFrame().setExtendedState(JFrame.NORMAL);
        SwingUtilities.invokeLater(new java.lang.Runnable() {
            public void run() {
                layout.rectangle = getMainFrame().getBounds();
            }
        });
    }

    /**
     * sets the orientation of the translation panel
     *
     * @param translation the orientation
     */
    void setTranslationOrientation(Translation translation) {
        translationOrientation = translation;
        int xMin = xSlider.slider.getMinimum();
        int xMax = xSlider.slider.getMaximum();
        int xValue = xSlider.slider.getValue();
        int xStep = xSlider.step;
        boolean xInverted = xSlider.slider.getInverted();

        int yMin = ySlider.slider.getMinimum();
        int yMax = ySlider.slider.getMaximum();
        int yValue = ySlider.slider.getValue();
        int yStep = ySlider.step;
        boolean yInverted = ySlider.slider.getInverted();

        int zMin = zSlider.slider.getMinimum();
        int zMax = zSlider.slider.getMaximum();
        int zValue = zSlider.slider.getValue();
        int zStep = zSlider.step;
        boolean zInverted = zSlider.slider.getInverted();

        switch(translation) {
            case XYZ:
                xSlider = translationPanel.firstSlider;
                ySlider = translationPanel.secondSlider;
                zSlider = translationPanel.thirdSlider;
                break;
            case XZY:
                xSlider = translationPanel.firstSlider;
                zSlider = translationPanel.secondSlider;
                ySlider = translationPanel.thirdSlider;
                break;
            case YXZ:
                ySlider = translationPanel.firstSlider;
                xSlider = translationPanel.secondSlider;
                zSlider = translationPanel.thirdSlider;
                break;
            case YZX:
                ySlider = translationPanel.firstSlider;
                zSlider = translationPanel.secondSlider;
                xSlider = translationPanel.thirdSlider;
                break;
            case ZXY:
                zSlider = translationPanel.firstSlider;
                xSlider = translationPanel.secondSlider;
                ySlider = translationPanel.thirdSlider;
                break;
            case ZYX:
                zSlider = translationPanel.firstSlider;
                ySlider = translationPanel.secondSlider;
                xSlider = translationPanel.thirdSlider;
                break;
        }
        xSlider.labeledTextField.label.setText("X");
        xSlider.setRange(xMin, xMax);
        xSlider.slider.setValue(xValue);
        xSlider.step = xStep;
        xSlider.slider.setInverted(xInverted);

        ySlider.labeledTextField.label.setText("Y");
        ySlider.setRange(yMin, yMax);
        ySlider.slider.setValue(yValue);
        ySlider.step = yStep;
        ySlider.slider.setInverted(yInverted);

        zSlider.labeledTextField.label.setText("Z");
        zSlider.setRange(zMin, zMax);
        zSlider.slider.setValue(zValue);
        zSlider.step = zStep;
        zSlider.slider.setInverted(zInverted);
    }

    /**
     * sets the orientation of the rotation panel
     *
     * @param rotation the orientation
     */
    void setRotationOrientation(Rotation rotation) {
        rotationOrientation = rotation;

        int pitchMin = pitchSlider.slider.getMinimum();
        int pitchMax = pitchSlider.slider.getMaximum();
        int pitchValue = pitchSlider.slider.getValue();
        int pitchStep = pitchSlider.step;
        boolean pitchInverted = pitchSlider.slider.getInverted();

        int yawMin = yawSlider.slider.getMinimum();
        int yawMax = yawSlider.slider.getMaximum();
        int yawValue = yawSlider.slider.getValue();
        int yawStep = yawSlider.step;
        boolean yawInverted = yawSlider.slider.getInverted();

        int rollMin = rollSlider.slider.getMinimum();
        int rollMax = rollSlider.slider.getMaximum();
        int rollValue = rollSlider.slider.getValue();
        int rollStep = rollSlider.step;
        boolean rollInverted = rollSlider.slider.getInverted();

        switch(rotation) {
            case PYR:
                pitchSlider = rotationPanel.firstSlider;
                yawSlider = rotationPanel.secondSlider;
                rollSlider = rotationPanel.thirdSlider;
                break;
            case PRY:
                pitchSlider = rotationPanel.firstSlider;
                rollSlider = rotationPanel.secondSlider;
                yawSlider = rotationPanel.thirdSlider;
                break;
            case YPR:
                yawSlider = rotationPanel.firstSlider;
                pitchSlider = rotationPanel.secondSlider;
                rollSlider = rotationPanel.thirdSlider;
                break;
            case YRP:
                yawSlider = rotationPanel.firstSlider;
                rollSlider = rotationPanel.secondSlider;
                pitchSlider = rotationPanel.thirdSlider;
                break;
            case RPY:
                rollSlider = rotationPanel.firstSlider;
                pitchSlider = rotationPanel.secondSlider;
                yawSlider = rotationPanel.thirdSlider;
                break;
            case RYP:
                rollSlider = rotationPanel.firstSlider;
                yawSlider = rotationPanel.secondSlider;
                pitchSlider = rotationPanel.thirdSlider;
                break;
        }

        pitchSlider.labeledTextField.label.setText("Pitch");
        pitchSlider.setRange(pitchMin, pitchMax);
        pitchSlider.slider.setValue(pitchValue);
        pitchSlider.step = pitchStep;
        pitchSlider.slider.setInverted(pitchInverted);

        yawSlider.labeledTextField.label.setText("Yaw");
        yawSlider.setRange(yawMin, yawMax);
        yawSlider.slider.setValue(yawValue);
        yawSlider.step = yawStep;
        yawSlider.slider.setInverted(yawInverted);

        rollSlider.labeledTextField.label.setText("Roll");
        rollSlider.setRange(rollMin, rollMax);
        rollSlider.slider.setValue(rollValue);
        rollSlider.step = rollStep;
        rollSlider.slider.setInverted(rollInverted);
    }

    /** connects to the simulation */
    @Action
    public void connect() throws IOException {
        super.connect();
        sendFullState();

        new SwingWorker<Void, Void>() {

            /** In a background Worker thread, forever listen for incoming messages from the Variable Server. */
            @Override
            public Void doInBackground() throws IOException {
                while (true) {
                    String line = variableServerConnection.get();
                    if (line == null) {
                        throw new IOException("Reached the end of the stream.");
                    }
                }
            }

            /** executed on the Event Dispatch Thread after the doInBackground method is finished */
            @Override
            protected void done() {
                try {
                    // Check for any exception that occurred during execution by calling get().
                    get();
                }
                catch (Exception exception) {
                    disconnect(exception);
                }
            }
        }.execute();
    }

    /** sends the full control state of the GUI to the simulation */
    void sendFullState() {
        //sendRateHold();
        //sendTrigger();
        //sendGrannularity();
        sendAllSliderValues();
    }

    /** sends the grannularity command to the simulation */
    void sendGrannularity() {
        if (grannularityRadioGroup.getSelectedValue().getText().equals("Coarse")) {
            sendToVariableServer(simObjectName + ".hc_data.Button_2 = 1");
        }
        else {
            sendToVariableServer(simObjectName + ".hc_data.Button_2 = 0");
        }
    }

    /** sends all of the slider values to the simulation */
    void sendAllSliderValues() {
        sendSliderValue(xSlider.slider);
        sendSliderValue(ySlider.slider);
        sendSliderValue(zSlider.slider);
        sendSliderValue(pitchSlider.slider);
        sendSliderValue(yawSlider.slider);
        sendSliderValue(rollSlider.slider);
    }

    /**
     * sends the specified slider value to the simulation
     *
     * @param slider the slider
     */
    void sendSliderValue(JSlider slider) {
        if (slider == xSlider.slider) {
            sendToVariableServer(simObjectName + ".inOutTranslation.setValue(" + xSlider.slider.getValue() + ")");
        }
        else if (slider == ySlider.slider) {
            sendToVariableServer(simObjectName + ".leftRightTranslation.setValue(" + ySlider.slider.getValue() + ")");
        }
        else if (slider == zSlider.slider) {
            sendToVariableServer(simObjectName + ".upDownTranslation.setValue(" + zSlider.slider.getValue() + ")");
        }
        else if (slider == pitchSlider.slider) {
            sendToVariableServer(simObjectName + ".upDownRotation.setValue(" + pitchSlider.slider.getValue() + ")");
        }
        else if (slider == yawSlider.slider) {
            sendToVariableServer(simObjectName + ".leftRightRotation.setValue(" + yawSlider.slider.getValue() + ")");
        }
        else {
            sendToVariableServer(simObjectName + ".clockwiseCounterclockwiseRotation.setValue(" + rollSlider.slider.getValue() + ")");
        }
    }

    /** sends the rate hold command to the simulation */
    void sendRateHold() {
        sendToVariableServer(simObjectName + ".hc_data.Button_1 = " + (rateHoldToggleButton.isSelected() ? "1" : "0"));
    }

    /** sends the trigger command to the simulation */
    void sendTrigger() {
        sendToVariableServer(simObjectName + ".hc_data.Trigger = " + ((4 - getSelectedIndex(triggerRadioGroup)) % 3));
    }

    /**
     * sends the specified command to the Variable Server
     *
     * @param command the command
     */
    void sendToVariableServer(String command) {
        if (getConnectionState()) {
            try {
                variableServerConnection.put(command);
            }
            catch (Exception exception) {
                disconnect(exception);
            }
        }
    }

    @Override
    protected void disconnect(Exception exception) {
        try {
            super.disconnect(exception);
        }
        catch (IOException ioException) {}
    }

    /**
     * sets the name of the hand controller's simulation object
     */
    void setSimObjectName(String name) {
        simObjectName = name;
        getMainFrame().setTitle(resourceMap.getString("Application.title") + " - " + name);
    }

    /**
     * gets the specified radio group's selected index
     *
     * @param  the radio group
     *
     * @return the selected index
     */
    int getSelectedIndex(JXRadioGroup radioGroup) {
        AbstractButton selection = radioGroup.getSelectedButton();
        for (int i = 0; i < radioGroup.getChildButtonCount(); ++i) {
            if (radioGroup.getChildButton(i) == selection) {
                return i;
            }
        }
        return -1;
    }

    /**
     * sets the specified radio group's selection to the specified index
     *
     * @param radioGroup the radio group
     * @param intdex     the index
     */
    void setSelection(JXRadioGroup<JRadioButton> radioGroup, int index) {
        radioGroup.setSelectedValue((JRadioButton)radioGroup.getChildButton(index));
    }

    /**
     * launch the GUI
     *
     * @param args command line arguments
     */
    public static void main(String args[]) {
        // For Macs, move the menu bar from the JFrame to the top of the screen.
        System.setProperty("apple.laf.useScreenMenuBar", "true");

        // For Macs, set the name of the application menu item.
        System.setProperty("com.apple.mrj.application.apple.menu.about.name", "Virtual Hand Controller");

        final java.awt.SplashScreen splashScreen = java.awt.SplashScreen.getSplashScreen();
        if (splashScreen != null) {
            final java.awt.Graphics2D graphics = splashScreen.createGraphics();
            if (graphics != null) {

                final String messages[] = {"Adding Hidden Agendas", "Adjusting Bell Curves", "Aesthesizing Industrial Areas",
                  "Aligning Covariance Matrices", "Applying Feng Shui Shaders", "Applying Theatre Soda Layer",
                  "Asserting Packed Exemplars", "Attempting to Lock Back-Buffer", "Binding Sapling Root System",
                  "Breeding Fauna", "Building Data Trees", "Bureacritizing Bureaucracies",
                  "Calculating Inverse Probability Matrices", "Calculating Llama Expectoration Trajectory",
                  "Calibrating Blue Skies", "Charging Ozone Layer", "Coalescing Cloud Formations", "Cohorting Exemplars",
                  "Collecting Meteor Particles", "Compounding Inert Tessellations", "Compressing Fish Files",
                  "Computing Optimal Bin Packing", "Concatenating Sub-Contractors", "Containing Existential Buffer",
                  "Debarking Ark Ramp", "Debunching Unionized Commercial Services", "Deciding What Message to Display Next",
                  "Decomposing Singular Values", "Decrementing Tectonic Plates", "Deleting Ferry Routes",
                  "Depixelating Inner Mountain Surface Back Faces", "Depositing Slush Funds",
                  "Destabilizing Economic Indicators", "Determining Width of Blast Fronts", "Deunionizing Bulldozers",
                  "Dicing Models", "Diluting Livestock Nutrition Variables", "Downloading Satellite Terrain Data",
                  "Exposing Flash Variables to Streak System", "Extracting Resources", "Factoring Pay Scale",
                  "Fixing Election Outcome Matrix", "Flood-Filling Ground Water", "Flushing Pipe Network",
                  "Gathering Particle Sources", "Generating Jobs", "Gesticulating Mimes", "Graphing Whale Migration",
                  "Hiding Willio Webnet Mask", "Implementing Impeachment Routine", "Increasing Accuracy of RCI Simulators",
                  "Increasing Magmafacation", "Initializing My Sim Tracking Mechanism",
                  "Initializing Rhinoceros Breeding Timetable", "Initializing Robotic Click-Path AI",
                  "Inserting Sublimated Messages", "Integrating Curves", "Integrating Illumination Form Factors",
                  "Integrating Population Graphs", "Iterating Cellular Automata", "Lecturing Errant Subsystems",
                  "Mixing Genetic Pool", "Modeling Object Components", "Mopping Occupant Leaks", "Normalizing Power",
                  "Obfuscating Quigley Matrix", "Overconstraining Dirty Industry Calculations",
                  "Partitioning City Grid Singularities", "Perturbing Matrices", "Pixalating Nude Patch",
                  "Polishing Water Highlights", "Populating Lot Templates", "Preparing Sprites for Random Walks",
                  "Prioritizing Landmarks", "Projecting Law Enforcement Pastry Intake", "Realigning Alternate Time Frames",
                  "Reconfiguring User Mental Processes", "Relaxing Splines", "Removing Road Network Speed Bumps",
                  "Removing Texture Gradients", "Removing Vehicle Avoidance Behavior", "Resolving GUID Conflict",
                  "Reticulating Splines", "Retracting Phong Shader", "Retrieving from Back Store",
                  "Reverse Engineering Image Consultant", "Routing Neural Network Infanstructure",
                  "Scattering Rhino Food Sources", "Scrubbing Terrain", "Searching for Llamas",
                  "Seeding Architecture Simulation Parameters", "Sequencing Particles", "Setting Advisor Moods",
                  "Setting Inner Deity Indicators", "Setting Universal Physical Constants",
                  "Sonically Enhancing Occupant-Free Timber", "Speculating Stock Market Indices", "Splatting Transforms",
                  "Stratifying Ground Layers", "Sub-Sampling Water Data", "Synthesizing Gravity", "Synthesizing Wavelets",
                  "Time-Compressing Simulator Clock", "Unable to Reveal Current Activity", "Weathering Buildings",
                  "Zeroing Crime Network"};

                   new java.lang.Thread() {
                        @Override
                        public void run() {
                            java.util.Random random = new java.util.Random();
                            java.awt.Rectangle rectangle = splashScreen.getBounds();
                            graphics.setFont(graphics.getFont().deriveFont(Font.BOLD, 13));
                            java.awt.FontMetrics fontMetrics = graphics.getFontMetrics();
                            while (splashScreen.isVisible()) {
                                graphics.setComposite(java.awt.AlphaComposite.Clear);
                                graphics.fillRect(0, 0, rectangle.width, rectangle.height);
                                graphics.setPaintMode();
                                String message = messages[random.nextInt(messages.length)];
                                int x = (rectangle.width - fontMetrics.stringWidth(message)) / 2;
                                int y = rectangle.height * 4 / 5;
                                graphics.setColor(Color.BLACK);
                                graphics.drawString(message, x - 1, y - 1);
                                graphics.drawString(message, x - 1, y + 1);
                                graphics.drawString(message, x + 1, y - 1);
                                graphics.drawString(message, x + 1, y + 1);
                                graphics.setColor(Color.WHITE);
                                graphics.drawString(message, x, y);
                                splashScreen.update();
                                try {
                                    java.lang.Thread.sleep(random.nextInt(1000) + 500);
                                }
                                catch (Exception e) {}
                            }
                        }
                    }.start();
            }
        }

        VirtualHandControllerMain.launch(VirtualHandControllerMain.class, args);
    }

}
