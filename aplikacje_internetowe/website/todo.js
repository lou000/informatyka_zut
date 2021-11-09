var mainTable = document.getElementById("mainTable")

var codeInput = document.getElementById("inputCode");
var taskInput = document.getElementById("inputTask");
var dateInput = document.getElementById("inputDate");

var codeSearch = document.getElementById("codeSearch")
var taskSearch = document.getElementById("taskSearch")
var dateSearch = document.getElementById("dateSearch")

var alertBox  = document.getElementById("alert")
var alertText = document.getElementById("alertText")

class Task {
    constructor(code, task, date) 
    {
        this.code = code;
        this.task = task;
        this.date = date;
      }
}

Date.prototype.isValid = function () 
{
    return this.getTime() === this.getTime();
};

// Fire filterElements when user types
codeSearch.addEventListener('input', function (evt) {
    filterElements();
});

taskSearch.addEventListener('input', function (evt) {
    filterElements();
});

dateSearch.addEventListener('input', function (evt) {
    filterElements();
});

// Hide alert when animation finishes
alertBox.addEventListener("animationend", (ev) => {
    if (ev.type === "animationend" && ev.animationName === "fadeOut") 
        alertBox.style.display = "none";
}, false);

function showAlert(text)
{
    alertText.innerHTML = text;
    alertBox.style.display = "block"; // show element
    alertBox.classList.toggle('active'); // start animation
}

function alertClose()
{
    alertBox.classList.toggle('active'); // start animation
    // at the end of animation eventListener fires and hides the alert
}

function validateInput(code, task, date)
{
    let valid = true
    var errorText = ""

    // Regex below means one letter uppercase or lowercase and two digits
    const regex = /^[a-zA-Z]([0-9]{2})$/;
    if(!regex.test(code))
    {
        valid = false;
        errorText += "Error: Invalid code input, code has to comprise of one letter and two digits.<br/>"
    }

    // Task has to be between 3 and 255 chars long, inclusive.
    if(!(task.length <= 255 && task.length >= 3))
    {
        valid = false;
        errorText += "Error: Invalid task input, task has to be between 3 and 255 characters long (inclusive).<br/>"
    }

    // We can have no date or valid date
    if(date !== "")
    {
        date = new Date(date)
        if(!date.isValid())
        {
            valid = false;
            errorText += "Error: Invalid code input, code has to comprise of one letter and two digits.<br/>"
        }
    }
    if(!valid)
        showAlert(errorText)
    return valid;
}

function createRow(code, task, date)
{
    var row = document.createElement("tr");
    row.className = "elementRow";

    // Code cell
    var col1 = document.createElement("td");
    col1.className = "col1";
    col1.appendChild(document.createTextNode(code.toUpperCase()));
    row.appendChild(col1);

    // Task cell
    var col2 = document.createElement("td");
    col2.className = "col2";
    col2.appendChild(document.createTextNode(task));
    row.appendChild(col2);

    // Date cell
    var col3 = document.createElement("td");
    col3.className = "col3";
    col3.id = date === "" ? "" : (new Date(date)).toJSON() // The id is used for locale independant date storage
    var date = date === "" ? "" : new Date(date).toLocaleDateString();
    col3.appendChild(document.createTextNode(date));
    row.appendChild(col3);

    // Buttons
    var col4 = document.createElement("td");
    col4.className = "col4";
    var span1 = document.createElement("span");
    var span2 = document.createElement("span");
    var icon = document.createElement("i");
    span1.className = "listButton edit";
    span1.onclick = editElement;
    span2.className = "listButton close";
    span2.onclick = removeElement;
    icon.className  = "fa fa-times";
    
    span1.appendChild(document.createTextNode("Edit"));
    span2.appendChild(icon);

    col4.appendChild(span1);
    col4.appendChild(span2);

    row.appendChild(col4);
    return row
}

function filterElements()
{
    // if the clearSearchBtn is not displayed then
    // we have only the taskSearch input, run filterElementsMobile
    var b = document.getElementById("clearSearchBtn")
    if(window.getComputedStyle(b).display === "none")
    {
        filterElementsMobile();
        return;
    }

    var code = codeSearch.value;
    var task = taskSearch.value;
    var date = dateSearch.value;

    // restore the rows
    for (let i = 0; i<mainTable.children.length; i++)
        mainTable.children[i].style.display = "";

    // Hide elements that match code
    if(code !== "")
        for (let i = 0; i<mainTable.children.length; i++) 
        {
            if(!mainTable.children[i].children[0].textContent.toUpperCase().includes(code.toUpperCase()))
                mainTable.children[i].style.display = "none";
        }

    // Hide elements that match task
    if(task !== "")
        for (let i = 0; i<mainTable.children.length; i++) 
        {
            if(!mainTable.children[i].children[1].textContent.toUpperCase().includes(task.toUpperCase()))
                mainTable.children[i].style.display = "none";
        }

    // Hide elements that match date
    date = new Date(date)
    if(date.isValid())
    {
        date = date.toLocaleDateString()
        for (let i = 0; i<mainTable.children.length; i++) 
        {
            var rowDate = new Date(mainTable.children[i].children[2].id).toLocaleDateString();
            if(rowDate !== date)
                mainTable.children[i].style.display = "none";
        }
    }
}

// For mobile displays we have only single search input
// we search one phrase in all the rows
function filterElementsMobile()
{
    var search = taskSearch.value;

    // restore the rows
    for (let i = 0; i<mainTable.children.length; i++)
        mainTable.children[i].style.display = "";
    
    // hide the rows not matching our search
    if(search !== "")
    {
        for (let i = 0; i<mainTable.children.length; i++) 
        {
            var matches = false;
            if(mainTable.children[i].children[0].textContent.toUpperCase().includes(search.toUpperCase()))
                matches = true;
            if(mainTable.children[i].children[1].textContent.toUpperCase().includes(search.toUpperCase()))
                matches = true;
            if(mainTable.children[i].children[2].textContent.toUpperCase().includes(search.toUpperCase()))
                matches = true;
            if(!matches)
                mainTable.children[i].style.display = "none";
        }
    }
}

function clearSearch()
{
    // Clear search input and restore all rows
    codeSearch.value = ""
    taskSearch.value = ""
    dateSearch.value = ""

    for (let i = 0; i<mainTable.children.length; i++)
        mainTable.children[i].style.display = "";
}

function updateLocalStorage()
{
    // We do this everytime we make any change, this is incredibly inefficiant
    // but no user will ever create enough tasks for it to matter

    var tasks = []
    for (let i = 0; i<mainTable.children.length; i++) 
    {
        var task = new Task()
        task.code = mainTable.children[i].children[0].textContent
        task.task = mainTable.children[i].children[1].textContent
        task.date = mainTable.children[i].children[2].id // json date is stored in id
        tasks.push(task)
    }
    localStorage.setItem("tasks", JSON.stringify(tasks));
}

function restoreRows()
{
    // Go through all the tasks in storage and create rows
    var tasks = JSON.parse(localStorage.getItem("tasks"));
    for(let i = 0; i<tasks.length; i++)
        mainTable.appendChild(createRow(tasks[i].code, tasks[i].task, tasks[i].date));
}

function removeElement() 
{
    var div = this.parentElement.parentElement;
    div.parentNode.removeChild(div);
    updateLocalStorage();
}

function addElement()
{
    var code = codeInput.value;
    var task = taskInput.value;
    var date = dateInput.value;
    if(!validateInput(code, task, date))
        return;

    // If the user is editing the row we replace it, otherwise add new row
    if(editedRow)
    {
        editedRow.parentNode.replaceChild(createRow(code, task, date), editedRow);
        clearInput();
    }
    else
        mainTable.appendChild(createRow(code, task, date));
    
        updateLocalStorage();
}

function editElement()
{
    editedRow = this.parentElement.parentElement;
    editedRow.style.backgroundColor = "#A4E5EB";
    btn = document.getElementById("addButton");
    btn.textContent = "Apply"
    codeInput.value = editedRow.children[0].textContent;
    taskInput.value = editedRow.children[1].textContent;
    date = new Date(editedRow.children[2].id);
    
    // This below is the date conversion that is required by the <input type="date">
    // This does not bring joy...

    var month = ('0' + (date.getMonth() + 1)).slice(-2)
    var day = ('0' + date.getDate()).slice(-2) 
    var godHelpMe = date.getFullYear()+"-"+month+"-"+day;

    dateInput.value = godHelpMe;
}

function stopEditing()
{
    if(editedRow)
    {
        editedRow.style.backgroundColor = "white";
        editedRow = null;
        btn = document.getElementById("addButton");
        btn.textContent = "Add"
    }
}

function clearInput()
{
    codeInput.value = ""
    taskInput.value = ""
    dateInput.value = ""
    stopEditing();
}


var editedRow = null;
restoreRows();