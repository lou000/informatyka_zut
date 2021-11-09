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

function validateInput(code, task, date)
{
    let valid = true

    // Regex below means one letter uppercase or lowercase and two digits
    const regex = new RegExp('^[a-zA-Z]\\d{2}');
    valid &= regex.test(code);

    // Task has to be between 3 and 255 chars long, inclusive.
    valid &= task.length <= 255 && task.length >= 3;

    // We can have no date or valid date
    if(date !== "")
    {
        date = new Date(date)
        valid &= date.isValid();
    }
    return valid;
}

function restoreRows()
{
    // Go through all the tasks in storage and create rows
    var mainTable = document.getElementById("mainTable")
    var tasks = JSON.parse(localStorage.getItem("tasks"));
    for(let i = 0; i<tasks.length; i++)
        mainTable.appendChild(createRow(tasks[i].code, tasks[i].task, tasks[i].date));
}

function filterElements()
{
    var mainTable = document.getElementById("mainTable")
    var code = document.getElementById("codeSearch").value;
    var task = document.getElementById("taskSearch").value;
    var date = document.getElementById("dateSearch").value;

    // Hide elements that match code
    if(code !== "")
        for (let i = 1; i<mainTable.children.length; i++) 
        {
            if(mainTable.children[i].children[0].textContent.toUpperCase() !== code.toUpperCase())
                mainTable.children[i].style.display = "none";
        }

    // Hide elements that match task
    if(task !== "")
        for (let i = 1; i<mainTable.children.length; i++) 
        {
            if(mainTable.children[i].children[1].textContent.toUpperCase() !== task.toUpperCase())
                mainTable.children[i].style.display = "none";
        }

    // Hide elements that match date
    date = new Date(date)
    if(date.isValid())
    {
        date = date.toLocaleDateString()
        for (let i = 1; i<mainTable.children.length; i++) 
        {
            var rowDate = new Date(mainTable.children[i].children[2].textContent).toLocaleDateString();
            if(rowDate !== date)
            {
                console.log(rowDate, date)
                mainTable.children[i].style.display = "none";
                console.log("removed")
            }
        }
    }
}

function clearSearch()
{
    // Clear search input and restore all rows
    var mainTable = document.getElementById("mainTable")
    document.getElementById("codeSearch").value = ""
    document.getElementById("taskSearch").value = ""
    document.getElementById("dateSearch").value = ""

    for (let i = 1; i<mainTable.children.length; i++)
        mainTable.children[i].style.display = "";
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

function updateLocalStorage()
{
    // We do this everytime we make any change, this is incredibly inefficiant
    // but no user will ever create enough tasks for it to matter
    const mainTable = document.getElementById("mainTable")

    var tasks = []
    for (let i = 1; i<mainTable.children.length; i++) 
    {
        var task = new Task()
        task.code = mainTable.children[i].children[0].textContent
        task.task = mainTable.children[i].children[1].textContent
        task.date = mainTable.children[i].children[2].textContent
        tasks.push(task)
    }
    localStorage.setItem("tasks", JSON.stringify(tasks));
}

function removeElement() 
{
    var div = this.parentElement.parentElement;
    div.parentNode.removeChild(div);
    updateLocalStorage();
}

function addElement()
{
    var mainTable = document.getElementById("mainTable")
    var code = document.getElementById("inputCode").value;
    var task = document.getElementById("inputTask").value;
    var date = document.getElementById("inputDate").value;
    if(!validateInput(code, task, date))
        return;
    if(!editedRow)
        mainTable.appendChild(createRow(code, task, date));
    else
    {
        editedRow.parentNode.replaceChild(createRow(code, task, date), editedRow);
        clearInput();
    }
    updateLocalStorage();
}

function editElement()
{
    editedRow = this.parentElement.parentElement;
    editedRow.style.backgroundColor = "#A4E5EB";
    btn = document.getElementById("addButton");
    btn.textContent = "Apply"
    document.getElementById("inputCode").value = editedRow.children[0].textContent;
    document.getElementById("inputTask").value = editedRow.children[1].textContent;
    date = new Date(editedRow.children[2].textContent);
    
    // This below is the date conversion that is required by the <input type="date">
    // This does not bring joy...

    var month = ('0' + (date.getMonth() + 1)).slice(-2)
    var day = ('0' + date.getDate()).slice(-2) 
    var godHelpMe = date.getFullYear()+"-"+month+"-"+day;

    document.getElementById("inputDate").value = godHelpMe;
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
    document.getElementById("inputCode").value = ""
    document.getElementById("inputTask").value = ""
    document.getElementById("inputDate").value = ""
    stopEditing();
}


var editedRow = null;
restoreRows();