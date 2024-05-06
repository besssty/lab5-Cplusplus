#include "editor.h" 
bool drawLine = false; 
bool drawRect = false; 
bool drawEllipse = false; 
bool drawPoint = false; 

//LineEdit begin 
void LineEditor::OnLBup(HWND hwnd, LPARAM lParam){
    drawLine = false; 
    OnPaint(hwnd); 
}
void LineEditor::OnPaint(HWND hwnd){
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

    SelectObject(hdc, hPen);
    SetROP2(hdc, R2_NOTXORPEN);
    MoveToEx(hdc, begin_pos.x, begin_pos.y, NULL);
    LineTo(hdc, end_pos.x, end_pos.y);

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}
void LineEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawLine) {
        OnPaint(hwnd);
        begin_pos.x = LOWORD(lParam);
        begin_pos.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}
void LineEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawLine = true;
    begin_pos.x = LOWORD(lParam);
    begin_pos.y = HIWORD(lParam);
    end_pos = begin_pos; 
    
}
//LineEdit end

//RecEdit begin
long save_pos[4] = { 0, 0, 0, 0 }; 
void RectangleEditor::OnPaint(HWND hwnd)
{
    int c_X = (begin_pos.x + end_pos.x) / 2;
    int c_Y = (begin_pos.y + end_pos.y) / 2;
    int wh = abs(begin_pos.x - end_pos.x);
    int ht = abs(begin_pos.y - end_pos.y);

    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); 
    
    SelectObject(hdc, hPen);
    SetROP2(hdc, R2_NOTXORPEN);
    if (end_pos.x < begin_pos.x)
    {
        if (end_pos.y < begin_pos.y)
        {
            save_pos[0] = c_X; 
            save_pos[1] = c_Y; 
            save_pos[2] = c_X - wh; 
            save_pos[3] = c_Y - ht; 
            Rectangle(hdc, c_X, c_Y, c_X - wh, c_Y - ht);
        }
        else
        {
            save_pos[0] = c_X;
            save_pos[1] = c_Y;
            save_pos[2] = c_X - wh;
            save_pos[3] = c_Y + ht;
            Rectangle(hdc, c_X, c_Y, c_X - wh, c_Y + ht);
        }
    }
    else
    {
        if (end_pos.y < begin_pos.y)
        {
            save_pos[0] = c_X;
            save_pos[1] = c_Y;
            save_pos[2] = c_X + wh;
            save_pos[3] = c_Y - ht;
            Rectangle(hdc, c_X, c_Y, c_X + wh, c_Y - ht);
        }
        else
        {
            save_pos[0] = c_X;
            save_pos[1] = c_Y;
            save_pos[2] = c_X + wh;
            save_pos[3] = c_Y + ht;
            Rectangle(hdc, c_X, c_Y, c_X + wh, c_Y + ht);
        }
    }

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}

void RectangleEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawRect = true;
    begin_pos.x = LOWORD(lParam);
    begin_pos.y = HIWORD(lParam);
    end_pos = begin_pos;
}

void RectangleEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    drawRect = false; 
    OnPaint(hwnd); 
    begin_pos.x = save_pos[0]; 
    begin_pos.y = save_pos[1]; 
    end_pos.x = save_pos[2]; 
    end_pos.y = save_pos[3]; 
}

void RectangleEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawRect){
        OnPaint(hwnd);
        end_pos.x = LOWORD(lParam);
        end_pos.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}
//RecEdit end

//EllipseEdit begin 
void EllipseEditor::OnLBdown(HWND hwnd, LPARAM lParam)
{
    drawEllipse = true; 
    begin_pos.x = LOWORD(lParam);
    begin_pos.y = HIWORD(lParam);
    end_pos = begin_pos; 
}

void EllipseEditor::OnLBup(HWND hwnd, LPARAM lParam)
{
    drawEllipse = false; 
    OnPaint(hwnd); 
} 

void EllipseEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawEllipse)
    {
        OnPaint(hwnd);
        end_pos.x = LOWORD(lParam);
        end_pos.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}

void EllipseEditor::OnPaint(HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

    SelectObject(hdc, hPen);

    SetROP2(hdc, R2_NOTXORPEN);

    Ellipse(hdc, begin_pos.x, begin_pos.y, end_pos.x, end_pos.y);

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
}
//EllipseEdit end

//PointEdit begin 
void PointEditor::OnLBup(HWND hwnd, LPARAM lParam) {
    drawPoint = false;
    OnPaint(hwnd);
}

void PointEditor::OnPaint(HWND hwnd) {

}

void PointEditor::OnMouseMove(HWND hwnd, LPARAM lParam)
{
    if (drawPoint) {
        OnPaint(hwnd);
        begin_pos.x = LOWORD(lParam);
        begin_pos.y = HIWORD(lParam);
        OnPaint(hwnd);
    }
}

void PointEditor::OnLBdown(HWND hwnd, LPARAM lParam){
    drawPoint = true;
    begin_pos.x = LOWORD(lParam);
    begin_pos.y = HIWORD(lParam);
}
//PointEdit end
void ShapeEditor::OnLBdown(HWND, LPARAM) {};
void ShapeEditor::OnLBup(HWND, LPARAM) {};
void ShapeEditor::OnMouseMove(HWND, LPARAM) {};
void ShapeEditor::OnPaint(HWND) {};