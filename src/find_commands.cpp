// ****** find_commands.cpp **********
// ****  William R. Good  ********

#include "XPLMDataAccess.h"
#include "XPLMUtilities.h"

#include "xbtn2cmd.h"

#include <cstdio>
#include <cstdlib>

#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void process_find_xplane_radios_commands()

{
  // g430n1 Commands
  g430n1_cdi_cmd = XPLMFindCommand("sim/GPS/g430n1_cdi");
  g430n1_chapter_dn_cmd = XPLMFindCommand("sim/GPS/g430n1_chapter_dn");
  g430n1_chapter_up_cmd = XPLMFindCommand("sim/GPS/g430n1_chapter_up");
  g430n1_clr_cmd = XPLMFindCommand("sim/GPS/g430n1_clr");
  g430n1_coarse_down_cmd = XPLMFindCommand("sim/GPS/g430n1_coarse_down");
  g430n1_coarse_up_cmd = XPLMFindCommand("sim/GPS/g430n1_coarse_up");
  g430n1_com_ff_cmd = XPLMFindCommand("sim/GPS/g430n1_com_ff");
  g430n1_cursor_cmd = XPLMFindCommand("sim/GPS/g430n1_cursor");
  g430n1_cvol_cmd = XPLMFindCommand("sim/GPS/g430n1_cvol");
  g430n1_direct_cmd = XPLMFindCommand("sim/GPS/g430n1_direct");
  g430n1_ent_cmd = XPLMFindCommand("sim/GPS/g430n1_ent");
  g430n1_fine_down_cmd = XPLMFindCommand("sim/GPS/g430n1_fine_down");
  g430n1_fine_up_cmd = XPLMFindCommand("sim/GPS/g430n1_fine_up");
  g430n1_fpl_cmd = XPLMFindCommand("sim/GPS/g430n1_fpl");
  g430n1_menu_cmd = XPLMFindCommand("sim/GPS/g430n1_menu");
  g430n1_msg_cmd = XPLMFindCommand("sim/GPS/g430n1_msg");
  g430n1_nav_com_tog_cmd = XPLMFindCommand("sim/GPS/g430n1_nav_com_tog");
  g430n1_nav_ff_cmd = XPLMFindCommand("sim/GPS/g430n1_nav_ff");
  g430n1_obs_cmd = XPLMFindCommand("sim/GPS/g430n1_obs");
  g430n1_page_dn_cmd = XPLMFindCommand("sim/GPS/g430n1_page_dn");
  g430n1_page_up_cmd = XPLMFindCommand("sim/GPS/g430n1_page_up");
  g430n1_popout_cmd = XPLMFindCommand("sim/GPS/g430n1_popout");
  g430n1_popup_cmd = XPLMFindCommand("sim/GPS/g430n1_popup");
  g430n1_proc_cmd = XPLMFindCommand("sim/GPS/g430n1_proc");
  g430n1_vnav_cmd = XPLMFindCommand("sim/GPS/g430n1_vnav");
  g430n1_vvol_cmd = XPLMFindCommand("sim/GPS/g430n1_vvol");
  g430n1_zoom_in_cmd = XPLMFindCommand("sim/GPS/g430n1_zoom_in");
  g430n1_zoom_out_cmd = XPLMFindCommand("sim/GPS/g430n1_zoom_out");

  // g430n2 Commands
  g430n2_cdi_cmd = XPLMFindCommand("sim/GPS/g430n2_cdi");
  g430n2_chapter_dn_cmd = XPLMFindCommand("sim/GPS/g430n2_chapter_dn");
  g430n2_chapter_up_cmd = XPLMFindCommand("sim/GPS/g430n2_chapter_up");
  g430n2_clr_cmd = XPLMFindCommand("sim/GPS/g430n2_clr");
  g430n2_coarse_down_cmd = XPLMFindCommand("sim/GPS/g430n2_coarse_down");
  g430n2_coarse_up_cmd = XPLMFindCommand("sim/GPS/g430n2_coarse_up");
  g430n2_com_ff_cmd = XPLMFindCommand("sim/GPS/g430n2_com_ff");
  g430n2_cursor_cmd = XPLMFindCommand("sim/GPS/g430n2_cursor");
  g430n2_cvol_cmd = XPLMFindCommand("sim/GPS/g430n2_cvol");
  g430n2_direct_cmd = XPLMFindCommand("sim/GPS/g430n2_direct");
  g430n2_ent_cmd = XPLMFindCommand("sim/GPS/g430n2_ent");
  g430n2_fine_down_cmd = XPLMFindCommand("sim/GPS/g430n2_fine_down");
  g430n2_fine_up_cmd = XPLMFindCommand("sim/GPS/g430n2_fine_up");
  g430n2_fpl_cmd = XPLMFindCommand("sim/GPS/g430n2_fpl");
  g430n2_menu_cmd = XPLMFindCommand("sim/GPS/g430n2_menu");
  g430n2_msg_cmd = XPLMFindCommand("sim/GPS/g430n2_msg");
  g430n2_nav_com_tog_cmd = XPLMFindCommand("sim/GPS/g430n2_nav_com_tog");
  g430n2_nav_ff_cmd = XPLMFindCommand("sim/GPS/g430n2_nav_ff");
  g430n2_obs_cmd = XPLMFindCommand("sim/GPS/g430n2_obs");
  g430n2_page_dn_cmd = XPLMFindCommand("sim/GPS/g430n2_page_dn");
  g430n2_page_up_cmd = XPLMFindCommand("sim/GPS/g430n2_page_up");
  g430n2_popout_cmd = XPLMFindCommand("sim/GPS/g430n2_popout");
  g430n2_popup_cmd = XPLMFindCommand("sim/GPS/g430n2_popup");
  g430n2_proc_cmd = XPLMFindCommand("sim/GPS/g430n2_proc");
  g430n2_vnav_cmd = XPLMFindCommand("sim/GPS/g430n2_vnav");
  g430n2_vvol_cmd = XPLMFindCommand("sim/GPS/g430n2_vvol");
  g430n2_zoom_in_cmd = XPLMFindCommand("sim/GPS/g430n2_zoom_in");
  g430n2_zoom_out_cmd = XPLMFindCommand("sim/GPS/g430n2_zoom_out");
}
