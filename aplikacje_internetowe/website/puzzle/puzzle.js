
class vec2 
{
    constructor(x, y)
    {
        this.x = x;
        this.y = y;
    }
}

class PuzzlePiece 
{
    constructor(id, size, canvasPos, currentPos, mask)
    {
        this.id = id;
        this.size = size;
        this.canvasPos = canvasPos;
        this.currentPos = currentPos;
        this.mask = mask;
    }
}

var puzzleRows = 3
var puzzleCols = 3
var pieces = []

var map = L.map('map').setView([51.505, -0.09], 13);
L.tileLayer('https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token={accessToken}', {
    attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors, Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
    maxZoom: 18,
    id: 'mapbox/streets-v11',
    tileSize: 512,
    zoomOffset: -1,
    accessToken: 'pk.eyJ1IjoiZGF3aWR6dXQiLCJhIjoiY2tpYnMzZDU0MGQ1cDJycGV3Mm9wNGV4YyJ9.cpMFsNQVlPtHcyxxj6LioA'
}).addTo(map);



// all sizes and positions are as % of the document
function generatePieces()
{
    map.removeLayer(marker)
    //clear all elements
    var elements = document.getElementsByClassName("puzzlePiece");
    while(elements.length > 0){
        elements[0].parentNode.removeChild(elements[0]);
    }

    // get map size
    leafletImage(map, function (err, canvas){
        if(err)
            console.log(err);
            canvas = canvas;
        console.log(canvas.width, canvas.height)

        let bottomDivRect = document.getElementById("bottom").getBoundingClientRect();
        let bPos = new vec2(bottomDivRect.left, bottomDivRect.top);
        let pSize = new vec2(canvas.width/puzzleCols, canvas.height/puzzleRows)

        for(let col = 0; col<puzzleCols; col++)
        for(let row = 0; row<puzzleRows; row++)
        {
            let id = col*puzzleCols+row;
            let cPos = new vec2(pSize.x*col, pSize.y*row)
            let rPos = new vec2(getRandom(bPos.x, document.documentElement.clientWidth-pSize.x), getRandom(bPos.y, document.documentElement.clientHeight-pSize.y));
            var puzzle = new PuzzlePiece(id, pSize, cPos, rPos, null)
            let puzzleCanvas = createPuzzlePiece(puzzle, canvas)
            document.body.appendChild(puzzleCanvas)
            pieces[id] = puzzle;
        }
    });
    map.addLayer(marker);
}


function createPuzzlePiece(puzzle, canvas)
{
    const placeholder = document.createElement('div');
    let pctPos = absToPct(puzzle.currentPos)
    let pctSize = absToPct(puzzle.size)
    placeholder.innerHTML = `<canvas class="puzzlePiece draggable" width="${puzzle.size.x}" height="${puzzle.size.y}" id="piece${puzzle.id}" style="width: ${pctSize.x}%; height: ${pctSize.y}%; left: ${pctPos.x}%; top: ${pctPos.y}%; position: absolute;" draggable="true""></canvas>`;
    var puzzleCanvas = placeholder.firstElementChild;
    puzzleCanvas.ondragstart = function() {
        return false;
    };
    puzzleCanvas.onmousedown = function(event) {
        if(!puzzleCanvas.draggable)
            return false;
        
        let shiftX = event.clientX - puzzleCanvas.getBoundingClientRect().left;
        let shiftY = event.clientY - puzzleCanvas.getBoundingClientRect().top;
      
        puzzleCanvas.style.zIndex = 1000;
      
        moveAt(event.pageX, event.pageY);
      
        function moveAt(pageX, pageY) {
            let v = new vec2(clamp(pageX - shiftX, 0, document.documentElement.clientWidth-puzzleCanvas.width), 
                             clamp(pageY - shiftY, 0, document.documentElement.clientHeight-puzzleCanvas.height));
            puzzle.currentPos = v;
            puzzleCanvas.style.left = absToPct(v).x + '%';
            puzzleCanvas.style.top  = absToPct(v).y + '%';
        }
      
        function onMouseMove(event) {
            moveAt(event.pageX, event.pageY);
        }
      
        document.addEventListener('mousemove', onMouseMove);
      
        document.onmouseup = function() {
            document.removeEventListener('mousemove', onMouseMove);
            puzzleCanvas.onmouseup = null;
            if(Math.abs(puzzle.currentPos.x-canvas.width-puzzle.canvasPos.x)<50 && 
               Math.abs(puzzle.currentPos.y-puzzle.canvasPos.y)<50)
            {
                let v = new vec2(clamp(puzzle.canvasPos.x+canvas.width, 0, document.documentElement.clientWidth-puzzleCanvas.width),
                                 clamp(puzzle.canvasPos.y, 0, document.documentElement.clientHeight-puzzleCanvas.height));
                puzzle.currentPos = v;
                puzzleCanvas.style.left = absToPct(v).x + '%';
                puzzleCanvas.style.top  = absToPct(v).y + '%';
                puzzleCanvas.setAttribute('draggable', 'false');
            }
            checkForCompletion()
        };
      
    };
    
    var ctx = puzzleCanvas.getContext('2d');
    // ctx.fillStyle = 'rgb(200, 0, 0)';
    // ctx.fillRect(0, 0, puzzleCanvas.width, puzzleCanvas.height);
    console.log("Creating puzzle at pos: "+ puzzle.size.x+", "+puzzle.size.y)
    ctx.drawImage(canvas, puzzle.canvasPos.x, puzzle.canvasPos.y, puzzle.size.x, puzzle.size.y, 0, 0, puzzle.size.x, puzzle.size.y);
    return puzzleCanvas;
}


function absToPct(pos)
{
    return new vec2(pos.x*100/document.documentElement.clientWidth, pos.y*100/document.documentElement.clientHeight);
}

function pctToAbs(pos)
{
    return new vec2(pos.x*document.documentElement.clientWidth/100, pos.y*document.documentElement.clientHeight/100);;
}

function getRandom(min, max) {
    return Math.random() * (max - min) + min;
}

function checkForCompletion(){
    var elements = document.getElementsByClassName("puzzlePiece");
    var complete = true
    console.log("checking")
    for(const element of elements)
        if(element.draggable)
            complete = false;
    
    if(complete)
        trySendNotification("Well done")
}

function trySendNotification(msg) {
    let title = "MAP PUZZLE";
    if (Notification.permission === 'granted') {
        let options = {body: msg,}
        let n = new Notification(title, options);
        setTimeout(n.close.bind(n), 3000);
    } else {
        Notification.requestPermission(function (permission) {
            // If the user accepts, let's create a notification
            let options = {body: msg,}
            if (permission === "granted") {
              var notification = new Notification(title, options);
            }
          });
    }
}

let marker = L.marker([51.505, -0.09]);
function getLocation() {
    if (!navigator.geolocation) {
        alert("Geolocation not available.");
    }
    map.removeLayer(marker)
    navigator.geolocation.getCurrentPosition((position) => {
        xCor = position.coords.latitude;
        yCor = position.coords.longitude;
        document.getElementById("latitude").innerText = xCor.toFixed(2);
        document.getElementById("longitude").innerText = yCor.toFixed(2);
        map.panTo([xCor, yCor])
        marker = L.marker([xCor, yCor]);
        map.addLayer(marker);
    }, (positionError) => {
        console.error(positionError);
    }, {
        enableHighAccuracy: false
    });
}

const clamp = (num, a, b) => Math.max(Math.min(num, Math.max(a, b)), Math.min(a, b));