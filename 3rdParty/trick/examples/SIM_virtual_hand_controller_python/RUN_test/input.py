trick.real_time_enable()
trick.exec_set_software_frame(0.1)

# import IDF's modules
sys.path.append(os.environ['IDF_HOME'] + "/3rdParty/trick/python")
import idf.config

# Launch the Virtual Hand Controller.
# The VHC needs to know the name of the variable into which to write its values.
# This is the full path from the top-level SimObject. The S_define declares an
# instance of our SimObject called "example" which contains an instance of
# VirtualLayout called "virtualLayout."
idf.config.launchVirtualController("example.virtualLayout")
