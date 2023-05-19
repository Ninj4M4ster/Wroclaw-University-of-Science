const express = require('express')
const router = express.Router();

const bodyParser = require('body-parser');
const https = require('https');

const db_controller = require("./../controller/db_controller");

// web app endpoints
router.use(express.static(__dirname + "/public"))

// get all notes
router.get('/note', (req, res) => {
    let notes = JSON.parse(db_controller.get_notes());
    res.render('all_notes', {
        notes: notes
    });
})

// get note by id
router.get('/note/:id', (req, res) => {
    let note = JSON.parse(db_controller.get_note_by_id(req.params.id));
    res.render('note', {
        id: id
    });
})

module.exports = router;