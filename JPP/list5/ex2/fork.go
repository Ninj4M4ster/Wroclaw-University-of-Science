package main

type Fork struct {
	is_clean     chan (bool)
	finish_work  chan (bool)
	change_state chan (bool)
}

func (f Fork) run() {
	clean := false
	break_loop := false
	for !break_loop {
		select {
		case <-f.finish_work:
			break_loop = true
		case <-f.is_clean:
			f.is_clean <- clean
		case new_state := <-f.change_state:
			clean = new_state
		}
	}
}
