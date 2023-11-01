#include "pathfinder.h"

static bool is_paths_equal(t_path *data, t_path *expected) {
	bool res = ((mx_strcmp(data->to, expected->to) == 0
	             || mx_strcmp(data->to, expected->from) == 0) &&
	            (mx_strcmp(data->from, expected->to) == 0
	             || mx_strcmp(data->from, expected->from) == 0));
	return res;
}

static void push_path(t_paths_list **routes_list, t_path *path) {
	if (path == NULL) {
		return;
	}
	t_paths_list *route = (t_paths_list *) mx_list_find_where(
			(t_list *) *routes_list, path,
			(t_comp_func *) is_paths_equal);

	if (!route) {
		mx_push_back((t_list **) routes_list, path);
		return;
	}
	mx_delete_path(path);
}

static void recalculate_neigbors_distance(t_stop *current) {
	for (t_connections_list *conn = current->connections; conn != NULL; conn = conn->next) {
		t_stop *neighbor = conn->data->first != current ? conn->data->first : conn->data->second;
		if (neighbor->is_visited) continue;
		long distance = current->distance_from_start + conn->data->distance;

		if (neighbor->distance_from_start > distance) {
			neighbor->distance_from_start = distance;
			mx_clear_list((t_list **) &neighbor->previous_stops);
			mx_push_back((t_list **) &neighbor->previous_stops, current);
		} else if (neighbor->distance_from_start == distance) {
			mx_push_back((t_list **) &neighbor->previous_stops, current);
		}
	}
}

static void prepare_to_search(t_stops_list *stops_list) {
	for (t_stops_list *p_list = stops_list;
	     p_list != NULL; p_list = p_list->next) {
		p_list->data->distance_from_start = MX_INT_MAX;
		mx_clear_list((t_list **) &p_list->data->previous_stops);
		p_list->data->previous_stops = NULL;
		p_list->data->is_visited = false;
	}
}

static t_stop *find_stop_with_shortest_path(t_stops_list *stops) {
	if (!stops) {
		return NULL;
	}

	t_stop *shortest_stop = NULL;

	for (t_stops_list *current = stops; current != NULL; current = current->next) {
		t_stop *current_stop = current->data;

		if (current_stop->is_visited) {
			continue;
		}
		if (!shortest_stop
		    || current_stop->distance_from_start < shortest_stop->distance_from_start) {
			shortest_stop = current_stop;
		}
	}

	return shortest_stop;
}

static void djekstra_alhorism(t_paths_list **routes_list, t_stops_list *stops_list, t_stop *start) {
	prepare_to_search(stops_list);
	start->distance_from_start = 0;

	for (int i = mx_list_size((t_list *) stops_list); i > 0; i--) {
		t_stop *stop = find_stop_with_shortest_path(stops_list);
		recalculate_neigbors_distance(stop);
		stop->is_visited = true;
	}

	for (t_stops_list *st_list = stops_list; st_list != NULL; st_list = st_list->next) {
		if (st_list->data->previous_stops == NULL) {
			continue;
		}
		push_path(routes_list, mx_create_path(st_list->data));
	}
}

t_paths_list *mx_find_all_routes(t_graph *graph) {
	t_paths_list *routes_list = NULL;

	for (t_stops_list *start = graph->stops; start != NULL; start = start->next) {
		djekstra_alhorism(&routes_list, graph->stops, start->data);
	}

	return routes_list;
}

