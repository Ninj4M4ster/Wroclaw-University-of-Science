with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Discrete_Random;


procedure main is
    phils_count: Integer := 4;
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

    type phils_arr is array(1..phils_count) of phil_acc;

    task type fork is
        entry IsClean(is_clean: out Boolean);
        entry FinishWork;
        entry ChangeForkState(is_clean: Boolean);
    end fork;

    type fork_acc is access fork;

    task type philosopher is
        entry Initialize(id : Integer; meals_count: Integer; f_r : fork_acc; f_l : fork_acc; p: phils_arr);
        entry AskForFork(left: Boolean; out_fork: out fork_acc);
        entry StopThinking;
        entry PassRequestedIdentifier(left: Boolean; out_fork: fork_acc);
    end philosopher;

    task type get_fork is
        entry RequestFork(left: Boolean; p: phils_arr; id: Integer; requested_id: Integer);
    end get_fork;
    task body get_fork is
    is_left: Boolean;
    phils_array: phils_arr;
    identifier: Integer;
    requested_identifier: Integer;
    out_fork: fork_acc := null;
    begin
        accept RequestFork(left: Boolean; p: phils_arr; id: Integer; requested_id: Integer) do
            is_left := left;
            phils_array := p;
            identifier := id;
            requested_identifier := requested_id;
        end RequestFork;
        phils_array(requested_identifier).AskForFork(is_left, out_fork);
        phils_array(identifier).PassRequestedIdentifier(is_left, out_fork);
    end get_fork;

    type get_fork_acc is access get_fork;

    --  Philosopher
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
        give_out_forks_after_eating: Boolean := true;
        left_id: Integer;
        right_id: Integer;
        fork_clean_state: Boolean;
        left_fork_get_req: get_fork_acc := null;
        right_fork_get_req: get_fork_acc := null;
    begin
        Reset(G);
        accept Initialize(id : Integer; meals_count: Integer; f_r : fork_acc; f_l : fork_acc; p: phils_arr) do
            identifier := id;
            meals_to_eat := meals_count;
            right_fork := f_r;
            left_fork := f_l;
            philosophers_arr := p;
        end Initialize;
        left_id := identifier - 1;
        if left_id = 0 then
            left_id := phils_count;
        end if;
        right_id := identifier + 1;
        if right_id > phils_count then
            right_id := 1;
        end if;
        while meals_to_eat > ate_meals loop
            if is_thinking then
                Put_Line("Philosopher" & Integer'Image(identifier) & " starts thinking");
                while is_thinking loop
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
                end loop;
                Put_Line("Philosopher" & Integer'Image(identifier) & " stops thinking");
            else
                --  Get both forks
                while left_fork = null or right_fork = null loop
                --  Put_Line(Integer'Image(identifier) & " enters");
                    --  Put_Line(Integer'Image(identifier) & " hungry");
                    if left_fork = null and left_fork_get_req = null then
                        left_fork_get_req := new get_fork;
                        left_fork_get_req.RequestFork(false, philosophers_arr, identifier, left_id);
                    end if;
                    if right_fork = null and right_fork_get_req = null then
                        right_fork_get_req := new get_fork;
                        right_fork_get_req.RequestFork(true, philosophers_arr, identifier, right_id);
                    end if;
                    select
                        accept AskForFork(left: Boolean; out_fork: out fork_acc) do
                            out_fork := null;
                            if left and left_fork /= null then
                                left_fork.IsClean(fork_clean_state);
                                if not fork_clean_state then
                                    left_fork.ChangeForkState(true);
                                    out_fork := left_fork;
                                    left_fork := null;
                                end if;
                            elsif right_fork /= null then
                                right_fork.IsClean(fork_clean_state);
                                if not fork_clean_state then
                                    right_fork.ChangeForkState(true);
                                    out_fork := right_fork;
                                    right_fork := null;
                                end if;
                            end if;
                        end AskForFork;
                    or
                        accept PassRequestedIdentifier(left: Boolean; out_fork: fork_acc) do 
                            if not left then
                                left_fork := out_fork;
                                left_fork_get_req := null;
                            else
                                right_fork := out_fork;
                                right_fork_get_req := null;
                            end if;
                        end PassRequestedIdentifier;
                    end select;
                end loop;
                --  Sleep for random time
                left_fork.ChangeForkState(false);
                right_fork.ChangeForkState(false);
                Put_Line("Philosopher" & Integer'Image(identifier) & " starts eating");
                delay Duration(Random(G));

                ate_meals := ate_meals + 1;
                Put_Line("Philosopher" & Integer'Image(identifier) & " ate" & Integer'Image(ate_meals) & " meal");
                --  TODO: Iff all meals ate, give out forks as long as possible
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
                        delay 0.5;
                        give_out_forks_after_eating := false;
                    end select;
                end loop;
                give_out_forks_after_eating := true;
                if meals_to_eat > ate_meals then
                    thinking_timer := new Timer;
                    is_thinking := true;
                    thinking_timer.Init(Random(G), philosophers_arr(identifier));
                else 
                    while left_fork /= null or right_fork /= null loop
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
                        end select;
                    end loop;
                end if;
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
    for i in 1 .. phils_count loop
        forks(i) := new fork;
        phils(i) := new philosopher;
    end loop;
    phils(1).Initialize(1, meals_to_eat, forks(1), forks(phils_count), phils);
    for i in 2 .. phils_count - 1 loop
        phils(i).Initialize(i, meals_to_eat, forks(i), null, phils);
    end loop;
    phils(phils_count).Initialize(phils_count, meals_to_eat, null, null, phils);
end main;