package main

const min_wait_time = 1.0
const max_wait_time = 5.0

func main() {
	philosophers_count := 5
	meals_to_eat := 5
	forks := make([]Fork, philosophers_count)
	philosophers := make([]Philosopher, philosophers_count)
	for i := 0; i < philosophers_count; i++ {
		philosophers[i] = Philosopher{id_: i,
			meals_count_:        meals_to_eat,
			phils_array:         &philosophers,
			request_fork:        make(chan *Philosopher),
			left_fork_requested: make(chan bool),
			receive_fork:        make(chan *Fork),
			fork_r:              nil,
			fork_l:              nil,
		}
		forks[i] = Fork{
			is_clean:     make(chan bool),
			finish_work:  make(chan bool),
			change_state: make(chan bool),
		}
		go forks[i].run()
	}
	philosophers[0].fork_r = &forks[0]
	philosophers[0].fork_l = &forks[len(forks)-1]
	for i := 1; i < philosophers_count-1; i++ {
		philosophers[i].fork_r = &forks[i]
	}
	finish_channel := make(chan (bool))
	count := 0
	for i := range philosophers {
		go philosophers[i].run(finish_channel)
	}
	for count < philosophers_count {
		<-finish_channel
		count++
	}
}
