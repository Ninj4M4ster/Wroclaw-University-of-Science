const express = require('express')
const router = express.Router();

const bodyParser = require('body-parser');


// web app endpoints

// get all notes
router.get('/note', (req, res) => {
    res.render('all_notes', {
        notes: ["a", "b"]
    });
})

// get note by id
router.get('/note/:id', (req, res) => {
    let id = req.params.id;
    res.render('note', {
        id: id
    });
})

module.exports = router;