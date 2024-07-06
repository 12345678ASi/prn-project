const express = require('express');
const multer = require('multer');
const app = express();
const port = 3000;

const storage = multer.memoryStorage();
const upload = multer({ storage: storage });

app.use(express.static('public'));

app.post('/detect-damage', upload.single('image'), (req, res) => {
    // Implement your backend logic for image processing and machine learning here
    // Return the result as a response
    res.json({ result: 'Damage detected!' });
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
