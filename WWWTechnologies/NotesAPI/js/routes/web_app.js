const express = require('express')
const router = express.Router();

const bodyParser = require('body-parser');
const https = require('https');

const db_controller = require("./../controller/db_controller");

// web app endpoints
router.use(express.static(__dirname + "/public"))

// get all notes
router.get('/note', (req, res) => {
    db_controller.get_notes().then((r => {
        res.render('all_notes', {
            notes: JSON.parse(r)
        });
    }));
});

// add new note
router.get('/note/add_new_note', (req, res) => {
    res.render('add_new_note');
});

// get note by id
router.get('/note/:id', (req, res) => {
    db_controller.get_note_by_title(req.params.id).then((r) => {
        const note = JSON.parse(r);
        if(Object.keys(note).length !== 0) {
            res.render('note', {
                note: note
            })
        } else {
            db_controller.get_notes().then((r) => {
                res.render('all_notes', {
                    notes: JSON.parse(r)
                });
            });
        }
    });
});

router.post("/note/find_note", (req, res) => {
    let title = req.body.searched_title;
    res.redirect(`/web_app/note/${title}`);
})

router.post("/delete_note/:id", (req, res) => {
    db_controller.delete_note(req.params.id).then((deletedCount) => {
        let status;
        if(deletedCount === 0) {
            console.log("got 0");
            status = "Could not delete a note.";
        } else {
            status = "Successfully deleted a note.";
            console.log("deleted succ");
        }
        db_controller.get_notes().then((r => {

            res.render('all_notes', {
                notes: JSON.parse(r)
            });
        }));
    });
})


module.exports = router;