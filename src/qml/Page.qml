import QtQuick 1.1

Rectangle
{
    radius: 10
    smooth: true
    
    gradient: Gradient {
        GradientStop { position: 0; color: "#77FFFFFF" }
        GradientStop { position: 1; color: "transparent" }
    }
}