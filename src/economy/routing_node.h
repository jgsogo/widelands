/*
 * Copyright (C) 2004, 2006-2009 by the Widelands Development Team
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

#ifndef S__ROUTING_NODE_H
#define S__ROUTING_NODE_H

#include <vector>

#include "cookie_priority_queue.h"
#include "logic/widelands_geometry.h"

namespace Widelands {

struct Flag;
class RoutingNode;
struct Road;

/***
 * /todo The get functions should be declared const
 */
struct RoutingNodeNeighbour {
	RoutingNodeNeighbour(RoutingNode * const f, int32_t const cost) :
		m_nb(f), m_cost(cost)
	{}
	RoutingNode * get_neighbour() {
		return m_nb;
	}
	int32_t get_cost() const {
		return m_cost;
	}

private:
	RoutingNode * m_nb;
	int32_t m_cost; /// Cost to get from me to the neighbour (Cost for road)
};
typedef std::vector<RoutingNodeNeighbour> RoutingNodeNeighbours;

/**
 * A routing node is a field with a cost attached to it
 * plus some status variables needed for path finding.
 *
 * The only routing Node in Widelands is a Flag currently,
 * this interface has been extracted to reduce coupling
 */
struct RoutingNode {
	struct LessCost {
		bool operator()(const RoutingNode & a, const RoutingNode & b) const {
			return a.cost() < b.cost();
		}
	};
	typedef cookie_priority_queue<RoutingNode, LessCost> Queue;

// The variables are only protected so that Test classes can use them
protected:
	friend struct Economy;
	friend struct Router;
	uint32_t      mpf_cycle;
	Queue::cookie mpf_cookie;
	int32_t       mpf_realcost; ///< real cost of getting to this flag
	RoutingNode * mpf_backlink; ///< flag where we came from
	int32_t       mpf_estimate; ///< estimate of cost to destination

public:
	RoutingNode() : mpf_cycle(0),
		mpf_realcost(0), mpf_backlink(0), mpf_estimate(0) {}
	virtual ~RoutingNode() {}

	void reset_path_finding_cycle() {
		mpf_cycle = 0;
	}

	int32_t cost() const {return mpf_realcost + mpf_estimate;}
	Queue::cookie & cookie() {return mpf_cookie;}

	virtual Flag & base_flag() = 0;
	virtual int32_t get_waitcost() const = 0;
	virtual void get_neighbours(RoutingNodeNeighbours &) = 0;
	virtual Coords get_position() const = 0;
};

}

#endif


