import QtQuick 1.1

Rectangle
{
    radius: 10
    
    gradient: Gradient {
        GradientStop { position: 0; color: "#77FFFFFF" }
        GradientStop { position: 1; color: "transparent" }
    }
}