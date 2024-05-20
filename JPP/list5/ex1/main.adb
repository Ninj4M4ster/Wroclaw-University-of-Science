with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Discrete_Random;


procedure main is
    phils_count: Integer := 5;
    meals_to_eat: Integer := 5;

    subtype time_wait_range is Integer range 1 .. 10;

    package R is new
        Ada.Numerics.Discrete_Random (time_wait_range);
    use R;

    type philosopher;

    type phil_acc is access philosopher;

    task type timer is
        entry Init(seconds: Integer; calling_phil: phil_acc);
    end timer;

    type timer_acc is access timer;

    type phils_arr is array(1..5) of phil_acc;

    task type fork is
        entry IsClean(is_clean: out Boolean);
        entry FinishWork;
        entry ChangeForkState(is_clean: Boolean);
    end fork;

    type fork_acc is access fork;

    --  Philosopher
    task type philosopher is
        entry Initialize(id : Integer; meals_count: Integer; f : fork_acc; p: phils_arr);
        entry AskForFork(left: Boolean; out_fork: out fork_acc);
        entry StopThinking;
    end philosopher;
    task body philosopher is
        identifier: Integer;
        G: Generator;
        ate_meals: Integer := 0;
        meals_to_eat: Integer;
        left_fork: fork_acc := null;
        right_fork: fork_acc := null;
        philosophers_arr: phils_arr;
        thinking_timer: timer_acc;
        is_thinking: Boolean := false;
        give_out_forks_after_eating: Boolean := false;
        left_id: Integer;
        right_id: Integer;
        fork_clean_state: Boolean;
    begin
        Reset(G);
        accept Initialize(id : Integer; meals_count: Integer; f : fork_acc; p: phils_arr) do
            identifier := id;
            meals_to_eat := meals_count;
            right_fork := f;
            philosophers_arr := p;
        end Initialize;
        left_id := identifier - 1;
        if left_id < 0 then
            left_id := phils_count - 1;
        end if;
        right_id := identifier + 1;
        if right_id > phils_count then
            right_id := 0;
        end if;
        while meals_to_eat > ate_meals loop
            if is_thinking then
                select
                    accept StopThinking do
                        is_thinking := false;
                    end;
                or
                    accept AskForFork(left: Boolean; out_fork: out fork_acc) do
                        if left then
                            left_fork.ChangeForkState(true);
                            out_fork := left_fork;
                            left_fork := null;
                        else
                            right_fork.ChangeForkState(true);
                            out_fork := right_fork;
                            right_fork := null;
                        end if;
                    end AskForFork;
                end select;
            else
                --  Get both forks
                Put_Line("Dupa");
                while left_fork = null or right_fork = null loop
                    --  TODO: Add another task for obtaining forks
                    if left_fork = null then
                        Put_Line("Dupa entry");
                        philosophers_arr(left_id).AskForFork(false, left_fork);
                        Put_Line("Dupa entry");
                    end if;
                    if right_fork = null then
                        philosophers_arr(right_id).AskForFork(true, right_fork);
                    end if;
                    Put_Line("Dupa entry");
                    select
                        accept AskForFork(left: Boolean; out_fork: out fork_acc) do
                        Put_Line("Dupa entr acc y");
                            out_fork := null;
                            if left then
                                left_fork.IsClean(fork_clean_state);
                                if not fork_clean_state then
                                    left_fork.ChangeForkState(true);
                                    out_fork := left_fork;
                                    left_fork := null;
                                end if;
                            else
                                right_fork.IsClean(fork_clean_state);
                                if not fork_clean_state then
                                    right_fork.ChangeForkState(true);
                                    out_fork := right_fork;
                                    right_fork := null;
                                end if;
                            end if;
                        end AskForFork;
                    end select;
                end loop;
                Put_Line("Dupa");
                --  Sleep for random time
                left_fork.ChangeForkState(false);
                right_fork.ChangeForkState(false);
                delay Duration(Random(G));

                ate_meals := ate_meals + 1;
                Put_Line("Philosopher " & Integer'Image(identifier) & " ate " & Integer'Image(ate_meals) & " meal");
                while give_out_forks_after_eating loop
                    select 
                        accept AskForFork(left: Boolean; out_fork: out fork_acc) do
                            if left then
                                left_fork.ChangeForkState(true);
                                out_fork := left_fork;
                                left_fork := null;
                            else
                                right_fork.ChangeForkState(true);
                                out_fork := right_fork;
                                right_fork := null;
                            end if;
                        end AskForFork;
                    or
                        delay 0.0;
                        give_out_forks_after_eating := false;
                    end select;
                end loop;
                give_out_forks_after_eating := true;
                thinking_timer := new Timer;
                thinking_timer.Init(Random(G), philosophers_arr(identifier));
            end if;
        end loop;
        if left_fork /= null then
            left_fork.FinishWork;
        end if;
        if right_fork /= null then
            right_fork.FinishWork;
        end if;
    end philosopher;


    task body timer is
        time: Integer;
        phil: phil_acc;
    begin
        select
            accept Init(seconds: Integer; calling_phil: phil_acc) do
                time := seconds;
                phil := calling_phil;
            end Init;
        end select;
        delay Duration(time);
        phil.StopThinking;
    end timer;

    --  Fork
    task body fork is
        clean: Boolean := false;
        break_loop: Boolean := false;
    begin
        while not break_loop loop 
            select
                accept FinishWork do
                    break_loop := true;
                end FinishWork;
            or
                accept IsClean(is_clean: out Boolean) do
                    is_clean := clean;
                end IsClean;
            or
                accept ChangeForkState(is_clean: Boolean) do
                    clean := is_clean;
                end ChangeForkState;
            end select;
        end loop;
    end fork;


    phils: phils_arr;
    forks: array(1 .. phils_count) of fork_acc;
begin
    for i in 1 .. 5 loop
        forks(i) := new fork;
        phils(i) := new philosopher;
        phils(i).Initialize(i, meals_to_eat, forks(i), phils);
    end loop;
end main;