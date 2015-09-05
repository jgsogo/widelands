dirname = path.dirname(__file__)

tribes:new_productionsite_type {
   msgctxt = "atlanteans_building",
   name = "atlanteans_hunters_house",
   -- TRANSLATORS: This is a building name used in lists of buildings
   descname = pgettext("atlanteans_building", "Hunter’s House"),
   directory = dirname,
   icon = dirname .. "menu.png",
   size = "small",

   buildcost = {
		log = 1,
		planks = 1,
		granite = 1
	},
	return_on_dismantle = {
		granite = 1
	},

   animations = {
		idle = {
			pictures = path.list_directory(dirname, "idle_\\d+.png"),
			hotspot = { 36, 44 },
		},
	},

   aihints = {
		prohibited_till = 60
   },

	working_positions = {
		atlanteans_hunter = 1
	},

   outputs = {
		"meat"
   },

	programs = {
		work = {
			-- TRANSLATORS: Completed/Skipped/Did not start hunting because ...
			descname = _"hunting",
			actions = {
				"sleep=35000",
				"worker=hunt"
			}
		},
	},
	out_of_resource_notification = {
		-- TRANSLATORS: "Game" means animals that you can hunt
		title = _"Out of Game",
		-- TRANSLATORS: "game" means animals that you can hunt
		message = _"The hunter working out of this hunter’s house can’t find any game in his work area.",
		productivity_threshold = 0
	},
}
