let find_note_menu_hidden = false;
const findNoteButton = document.getElementById("findNoteButton");
const menu = document.getElementById("find_note_menu");
const hide_body_div = document.getElementById("hide_body_div");

findNoteButton.addEventListener("click", (e) => {
    menu.classList.remove("hidden");
    hide_body_div.classList.remove("hidden");
    e.stopImmediatePropagation();
});

menu.addEventListener("click", (e) => {
    e.stopImmediatePropagation();
});
document.body.addEventListener("click", (e) => {
    if(e.currentTarget !== findNoteButton && e.currentTarget !== menu) {
        menu.classList.add("hidden");
        hide_body_div.classList.add("hidden");
    }
});
