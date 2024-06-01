package main

func RequestFork(left bool, phils_arr *[]Philosopher, id int, requested_id int) {
	(*phils_arr)[requested_id].request_fork <- &(*phils_arr)[id]
	(*phils_arr)[requested_id].left_fork_requested <- left
}
