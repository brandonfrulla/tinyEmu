/**int a = 1; b = 2; c = 3;

switch (a) {  
    case 1:    
        a = b + c;    
        break;  
    case 2:    
        a = b - c;    
        break;  
    case 3:    
        a = b * c;    
        break;  
    case 4:    
        a = b / c;    
        break;  
    case 5:    
        a = b & c;    
        break;  
    case 6:    
        a = b | c;    
        break;  
    case 7:    
        a = b ^ c;
        break;  
    default:    
        a = 0;
} */

// switchstatement.s
// emu $ r d 400
// emu $ m 400 0 
// emu $ m 404 a
// emu $ m 408 1
main:
