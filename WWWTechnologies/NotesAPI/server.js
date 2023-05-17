const express = require('express')
const app = express()
const port = 3000

const bodyParser = require('body-parser');

//To parse URL encoded data
app.use(bodyParser.urlencoded({ extended: false }))

//To parse json data
app.use(bodyParser.json())

app.set('view engine', 'pug')
app.set('views','./views');

// get all notes
app.get('/note', (req, res) => {
    res.render('all_notes', {
        notes: ["a", "b"]
    });
})

// get note by id
app.get('/note/:id', (req, res) => {
    let id = req.params.id;
    res.render('note', {
        id: id
    });
})

// create new note
app.post('/note', (req, res) => {

})

// actualize note by id
app.put('/note/:id', (req, res) => {

})

// delete note by id
app.delete('/note/:id', (req, res) => {

})

app.listen(port, () => {
    console.log(`Listening on port ${port}`)
})