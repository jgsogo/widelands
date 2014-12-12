dirname = path.dirname(__file__)

animations = {
   idle = {
      pictures = { dirname .. "idle_\\d+.png" },
      hotspot = { 9, 24 }
   }
}
add_worker_animations(animations, "walk", dirname, "walk", {10, 23}, 10)
add_worker_animations(animations, "walkload", dirname, "walkload", {10, 24}, 10)


tribes:new_worker_type {
   name = "barbarians_innkeeper",
   -- TRANSLATORS: This is a worker name used in lists of workers
   descname = _"Innkeeper",

   buildcost = {
		barbarians_carrier = 1,
		kitchen_tools = 1
	},

	-- TRANSLATORS: Helptext for a worker: Innkeeper
   helptext = _"Produces food for miners.",
   animations = animations,
}
