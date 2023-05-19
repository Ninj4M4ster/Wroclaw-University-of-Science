const { MongoClient } = require("mongodb");

const uri = "mongodb+srv://guest:guest@notes.yqwqtui.mongodb.net/?retryWrites=true&w=majority";

const client = new MongoClient(uri);

module.exports = {
    get_notes: function () {
        const database = client.db("notes");
        const notes = database.collection("notes");
        return JSON.stringify(notes.find({}).toArray());
    },
    get_note_by_id: function(id) {
        const database = client.db("notes");
        const notes = database.collection("notes");
        return JSON.stringify(notes.find({_id: id}).toArray());
    }
}