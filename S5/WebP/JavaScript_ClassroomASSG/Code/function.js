
document.addEventListener("DOMContentLoaded", bindEvents);

function bindEvents(){
    document.getElementById('calc_btn').addEventListener("click",callCalc);
}

function validate_operands()
{
    var op1 = document.form1.op1.value;
    var op2 = document.form1.op2.value;
    var optn = document.form1.op.value;
    if(op1=="" || op2=="")
    {
        alert('Enter values in operand fields!');
        return false;
    }
    if(isNaN(op1) || isNaN(op2))
    {
        alert('Enter NUMERIC values in operand fields!');
        return false;
    }
    if(optn==""){
        alert('Please select operation!');
        return false;
    }
    return true;
}

function callCalc()
{
    if(!validate_operands())
        return;
    var result = "r ";
    var op1 = Number(document.form1.op1.value);
    var op2 = Number(document.form1.op2.value);
    var operation = document.form1.op.value;
    switch(operation){
        case '+': result = op1 + op2;
        break;
        case '-': result = op1 - op2;
        break;
        case 'x': result = op1 * op2;
        break;
        default: alert('Operation not Identified!');
        break;
    }
    
    //Floating point results are rounded to 2 decimal places
    try{
        if(result.toString().indexOf('.')>-1)
        result = result.toFixed(2);
    }
    catch(e){
        alert(e);
    }
    var result_str = op1 +" "+ operation +" "+ op2 + " = " + result;
    
    alert(result_str);
    document.getElementById("result").innerHTML = "Result : " +result_str;
}