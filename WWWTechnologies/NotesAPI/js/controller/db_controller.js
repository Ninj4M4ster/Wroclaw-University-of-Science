const { MongoClient } = require("mongodb");

const uri = "mongodb+srv://guest:guest@notes.yqwqtui.mongodb.net/?retryWrites=true&w=majority";

const client = new MongoClient(uri);

module.exports = {
    get_notes: async function () {
        const database = client.db("notes");
        const notes = database.collection("notes");
        const final_data = {}
        const cursor = notes.find({});
        let i = 0;
        for await(const doc of cursor) {
            final_data[i] = ({"title": doc.title, "data": doc.data});
            i++;
        }
        return JSON.stringify(final_data);
    },

    get_note_by_id: async function(id) {
        const database = client.db("notes");
        const notes = database.collection("notes");
        const cursor = notes.find({_id: id});
        const final_data = {};
        for await(const doc of cursor) {
            final_data["title"] = doc.title;
            final_data["data"] = doc.data;
        }
        return JSON.stringify(final_data);
    },

    add_note: function(data) {
        const database = client.db('notes');
        const notes = database.collection('notes');
        let result = false;
        notes.insertOne(data).then(r => result = true);
        return result;
    },

    delete_note: async function(note_title) {
        const database = client.db("notes");
        const notes = database.collection('notes');
        let result;
        await notes.deleteOne({"title": note_title}).then((r) => {
            result = parseInt(r.deletedCount);
        });
        return result;
    }
}