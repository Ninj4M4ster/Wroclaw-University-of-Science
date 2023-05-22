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
    db_controller.get_note_by_id(req.params.id).then((r) => {
        console.log(r);
    })
});

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