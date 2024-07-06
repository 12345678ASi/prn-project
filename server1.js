const express = require('express');
const multer = require('multer');
const app = express();
const port = 5000;

// Configure Multer for file uploads
const upload = multer({ dest: 'uploads/' });

app.use(express.json());

app.post('/detect', upload.single('image'), (req, res) => {
    // Simulate damage detection
    const damageType = 'Scratch';  // This would be detected by a real ML model
    const estimatedCost = 200;     // Estimated repair cost
    const estimatedTime = 3;       // Estimated repair time in hours

    // Send the response
    res.json({
        damageType: damageType,
        estimatedCost: estimatedCost,
        estimatedTime: estimatedTime
    });
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
