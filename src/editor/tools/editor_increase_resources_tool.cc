/*
 * Copyright (C) 2002-2004, 2006 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "editor_increase_resources_tool.h"
#include "graphic.h"
#include "map.h"
#include "field.h"
#include "editorinteractive.h"
#include "world.h"
#include "map.h"
#include "error.h"
#include "overlay_manager.h"
#include "worlddata.h"

/*
=============================

class Editor_Increase_Resources_Tool

=============================
*/
int Editor_Change_Resource_Tool_Callback(const TCoords c, void * data, int curres) {
	Map & map = *static_cast<Map * const>(data);
	FCoords f = FCoords(c, map.get_field(c));

   FCoords f1;
   int count=0;

   // This field
	count += f.field->get_terr().resource_value(curres);
	count += f.field->get_terd().resource_value(curres);


   // If one of the neighbours is unpassable, count its resource stronger
   // top left neigbour
   map.get_neighbour(f, Map_Object::WALK_NW, &f1);
	count += f1.field->get_terr().resource_value(curres);
	count += f1.field->get_terd().resource_value(curres);

   // top right neigbour
   map.get_neighbour(f, Map_Object::WALK_NE, &f1);
	count += f1.field->get_terd().resource_value(curres);

   // left neighbour
   map.get_neighbour(f, Map_Object::WALK_W, &f1);
	count += f1.field->get_terr().resource_value(curres);

   if(count<=3)
      return 0;
   else
      return f.field->get_caps();
}

/*
===========
Editor_Increase_Resources_Tool::handle_click_impl()

decrease the resources of the current field by one if
there is not already another resource there.
===========
*/
int Editor_Increase_Resources_Tool::handle_click_impl(FCoords& fc, Map* map, Editor_Interactive* parent) {
   MapRegion mrc(map, fc, parent->get_fieldsel_radius());
   FCoords c;

   while(mrc.next(&c)) {
      Field* f=map->get_field(c);

      int res=f->get_resources();
      int amount=f->get_resources_amount();
      int max_amount=map->get_world()->get_resource(m_cur_res)->get_max_amount();

      amount+=m_changed_by;
      if(amount>max_amount) amount=max_amount;


      if((res==m_cur_res || !res) && Editor_Change_Resource_Tool_Callback(c,map,m_cur_res)) {
         // Ok, we're doing something. First remove the current overlays
         std::string str;
         str=map->get_world()->get_resource(res)->get_editor_pic(f->get_resources_amount());
         int picid=g_gr->get_picture( PicMod_Menu,  str.c_str() );
         map->get_overlay_manager()->remove_overlay(c,picid);

         if(!amount) {
            f->set_resources(0,0);
            f->set_starting_res_amount(0);
         } else {
            f->set_resources(m_cur_res,amount);
            f->set_starting_res_amount(amount);
            // set new overlay
            str=map->get_world()->get_resource(m_cur_res)->get_editor_pic(amount);
            int picid=g_gr->get_picture( PicMod_Menu,  str.c_str() );
            map->get_overlay_manager()->register_overlay(c,picid,4);
            map->recalc_for_field_area(c,0);
         }
      }
   }
   return parent->get_fieldsel_radius();
}
