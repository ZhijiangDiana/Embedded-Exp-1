########################################################################
#
#                           GettingStarted.eww
#
# $Revision: 39069 $
#
########################################################################

DESCRIPTION
===========
   This example project shows how to use the IAR Embedded Workbench for ARM
  to develop code for IAR KSK-MB9BF506 board. It shows basic use of I/O,
  Dual timer and the interrupt controller.

COMPATIBILITY
=============

   The example project is compatible with IAR FSSDC-9B506-EK board. By default,
  the project is configured to use the M-Link SWD interface.

CONFIGURATION
=============

  The GettingStarted application is downloaded to the iFlash or iRAM memory
  depending on selected configuration and executed.

GETTING STARTED
===============

  1) Start the IAR Embedded Workbench for ARM.

  2) Select File->Open->Workspace...
     Open the following workspace:

      <installation-root>\arm\examples\Fujitsu\
     MB9BF50x\KSK-MB9BF506\GettingStarted\GettingStarted.eww

  3) Select configuration.

  4) Power the board and connect the J-Link.
 
  5) Press CTRL+D or use Download and Debug button to start a debug session.