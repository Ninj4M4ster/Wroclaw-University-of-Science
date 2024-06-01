package main

import (
	"fmt"
	"math/rand/v2"
	"time"
)

type Philosopher struct {
	id_                 int
	meals_count_        int
	fork_r              *Fork
	fork_l              *Fork
	phils_array         *[]Philosopher
	request_fork        chan (*Philosopher)
	left_fork_requested chan (bool)
	receive_fork        chan (*Fork)
}

func (phil Philosopher) run(finish_channel chan (bool)) {
	is_thinking := false
	var thinking_timer time.Timer
	left_id := phil.id_ - 1
	if left_id < 0 {
		left_id = len(*phil.phils_array) - 1
	}
	right_id := phil.id_ + 1
	if right_id == len(*phil.phils_array) {
		right_id = 0
	}
	ate_meals := 0
	left_fork_requested := false
	right_fork_requested := false
	for phil.meals_count_ > ate_meals {
		if is_thinking {
			fmt.Println("Philosopher", phil.id_, "starts thinking")
			for is_thinking {
				select {
				case <-thinking_timer.C:
					is_thinking = false
				case asking_phil := <-phil.request_fork:
					left := <-phil.left_fork_requested
					if left {
						phil.fork_l.change_state <- true
						asking_phil.receive_fork <- phil.fork_l
						asking_phil.left_fork_requested <- true
						phil.fork_l = nil
					} else {
						phil.fork_r.change_state <- true
						asking_phil.receive_fork <- phil.fork_r
						asking_phil.left_fork_requested <- false
						phil.fork_r = nil
					}
				}
			}
			fmt.Println("Philosopher", phil.id_, "stopped thinking")
		} else {
			for phil.fork_l == nil || phil.fork_r == nil {
				if phil.fork_l == nil && !left_fork_requested {
					go RequestFork(false, phil.phils_array, phil.id_, left_id)
					left_fork_requested = true
				}
				if phil.fork_r == nil && !right_fork_requested {
					go RequestFork(true, phil.phils_array, phil.id_, right_id)
					right_fork_requested = true
				}
				select {
				case asking_phil := <-phil.request_fork:
					left := <-phil.left_fork_requested
					if left && phil.fork_l != nil {
						phil.fork_l.is_clean <- true
						is_fork_clean := <-phil.fork_l.is_clean
						if !is_fork_clean {
							phil.fork_l.change_state <- true
							asking_phil.receive_fork <- phil.fork_l
							asking_phil.left_fork_requested <- true
							phil.fork_l = nil
						} else {
							asking_phil.receive_fork <- nil
							asking_phil.left_fork_requested <- true
						}
					} else if phil.fork_r != nil {
						phil.fork_r.is_clean <- true
						is_fork_clean := <-phil.fork_r.is_clean
						if !is_fork_clean {
							phil.fork_r.change_state <- true
							asking_phil.receive_fork <- phil.fork_r
							asking_phil.left_fork_requested <- false
							phil.fork_r = nil
						} else {
							asking_phil.receive_fork <- nil
							asking_phil.left_fork_requested <- false
						}
					}
				case received_fork := <-phil.receive_fork:
					is_left := <-phil.left_fork_requested
					if !is_left {
						phil.fork_l = received_fork
						left_fork_requested = false
					} else {
						phil.fork_r = received_fork
						right_fork_requested = false
					}
				}
			}
			// change forks states
			phil.fork_l.change_state <- false
			phil.fork_r.change_state <- false
			// eat
			fmt.Println("Philosopher", phil.id_, "starts eating")
			timer := time.NewTimer(time.Duration(rand.Float64()*(max_wait_time-min_wait_time)+min_wait_time) * time.Second)
			<-timer.C

			ate_meals += 1
			fmt.Println("Philosopher", phil.id_, "ate", ate_meals, "meals")
			// give out forks
			give_out_forks_after_eating := true
			for give_out_forks_after_eating {
				select {
				case asking_phil := <-phil.request_fork:
					left := <-phil.left_fork_requested
					if left {
						phil.fork_l.change_state <- true
						asking_phil.receive_fork <- phil.fork_l
						asking_phil.left_fork_requested <- true
						phil.fork_l = nil
					} else {
						phil.fork_r.change_state <- true
						asking_phil.receive_fork <- phil.fork_r
						asking_phil.left_fork_requested <- false
						phil.fork_r = nil
					}
				default:
					give_out_forks_after_eating = false
				}
			}
			if phil.meals_count_ > ate_meals {
				// create thinking timer
				is_thinking = true
				thinking_timer = *time.NewTimer(time.Duration(rand.Float64()*(max_wait_time-min_wait_time)+min_wait_time) * time.Second)
			} else {
				finish_channel <- true
				for phil.fork_l != nil || phil.fork_r != nil {
					asking_phil := <-phil.request_fork
					left := <-phil.left_fork_requested
					if left {
						phil.fork_l.change_state <- true
						asking_phil.receive_fork <- phil.fork_l
						asking_phil.left_fork_requested <- true
						phil.fork_l = nil
					} else {
						phil.fork_r.change_state <- true
						asking_phil.receive_fork <- phil.fork_r
						asking_phil.left_fork_requested <- false
						phil.fork_r = nil
					}
				}
			}
		}
	}
	if phil.fork_l != nil {
		phil.fork_l.finish_work <- true
	}
	if phil.fork_r != nil {
		phil.fork_r.finish_work <- true
	}
}
