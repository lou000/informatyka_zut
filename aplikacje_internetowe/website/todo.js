class Task {
    constructor(code, task, date) {
        this.code = code;
        this.task = task;
        this.date = date;
      }
}

function createRow(code, task, date){
    var row = document.createElement("tr");
    row.className = "elementRow";

    var col1 = document.createElement("td");
    col1.className = "col1";
    col1.appendChild(document.createTextNode(code));
    row.appendChild(col1);

    var col2 = document.createElement("td");
    col2.className = "col2";
    col2.appendChild(document.createTextNode(task));
    row.appendChild(col2);

    var col3 = document.createElement("td");
    col3.className = "col3";
    col3.appendChild(document.createTextNode(date));
    row.appendChild(col3);

    var col4 = document.createElement("td");
    col4.className = "col4";
    var span1 = document.createElement("span");
    var span2 = document.createElement("span");
    var icon = document.createElement("i");
    span1.className = "listButton edit";
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

function updateLocalStorage(){
    const mainTable = document.getElementById("mainTable")

    var tasks = []
    for (let i = 0; i<mainTable.children.length; i++) 
    {
        var task = new Task()
        if(mainTable.children[i].className === "elementRow")
        {
            
            task.code = mainTable.children[i].children[0].textContent
            task.task = mainTable.children[i].children[1].textContent
            task.date = mainTable.children[i].children[2].textContent
            console.log(task)
            tasks.push(task)
        }
    }
    localStorage.setItem("tasks", JSON.stringify(tasks));
}

function removeElement() {
    var div = this.parentElement.parentElement;
    div.parentNode.removeChild(div);
    updateLocalStorage();
}

document.getElementById("addButton").onclick = addElement;
function addElement(){
    var mainTable = document.getElementById("mainTable")
    var code = document.getElementById("inputCode").value;
    var task = document.getElementById("inputTask").value;
    var date = document.getElementById("inputDate").value;
    mainTable.appendChild(createRow(code, task, date));
    updateLocalStorage();
}

function clearInput(){
    document.getElementById("inputCode").value = ""
    document.getElementById("inputTask").value = ""
    document.getElementById("inputDate").value = ""
}
