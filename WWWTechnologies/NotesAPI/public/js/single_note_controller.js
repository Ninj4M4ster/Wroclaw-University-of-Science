function show_form(note_title) {
    console.log(note_title);
    const div_el = document.getElementById(note_title + "_data");
    const form = document.getElementById(note_title + "_form");
    const update_span = document.getElementById(note_title + "_update_icon");
    const confirm_span = document.getElementById(note_title + "_confirm_icon");
    console.log(form.classList);
    if(form.classList.contains('hidden_form')) {
        form.classList.remove("hidden_form");
        div_el.classList.add("hidden_form");
        update_span.classList.add("hidden_icon");
        confirm_span.classList.remove("hidden_icon");
    } else {
        form.classList.add("hidden_form");
        form.submit();
        div_el.classList.remove("hidden_form");
        update_span.classList.remove("hidden_icon");
        confirm_span.classList.add("hidden_icon");
    }
}