import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Line2D.Double;
import java.awt.geom.Rectangle2D.Double;
import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import javax.swing.JPanel;

class EasyJPanel extends JPanel
{
  private int width;
  private int height;
  private int currentX = 0;
  private int currentY = 0;
  private Color currentColor = new Color(0, 0, 0);
  private BufferedImage image = null;
  private ColorModel colorModel;
  private Graphics2D g2image;

  public EasyJPanel(int paramInt1, int paramInt2)
  {
    this.width = paramInt1;
    this.height = paramInt2;
    setPreferredSize(new Dimension(paramInt1, paramInt2));
    this.image = new BufferedImage(paramInt1, paramInt2, 2);
    this.colorModel = this.image.getColorModel();
    setBackground(Color.white);
    this.g2image = this.image.createGraphics();
  }

  public void paintComponent(Graphics paramGraphics)
  {
    super.paintComponent(paramGraphics);
    Graphics2D localGraphics2D = (Graphics2D)paramGraphics;
    localGraphics2D.drawImage(this.image, 0, 0, null);
  }

  public void sub_690()
  {
    Rectangle2D.Double localDouble = new Rectangle2D.Double(0.0D, 0.0D, this.width, this.height);
    this.g2image.setColor(Color.white);
    this.g2image.fill(localDouble);
    repaint();
  }

  public void sub_6d5(String paramString, int paramInt1, int paramInt2)
  {
    this.g2image.drawString(paramString, paramInt1, sub_7f6(paramInt2));
    repaint();
  }

  public void sub_702(int paramInt1, int paramInt2)
  {
    this.currentX = paramInt1;
    this.currentY = sub_7f6(paramInt2);
  }

  public void sub_72b(int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    sub_702(paramInt3, paramInt4);
    Line2D.Double localDouble = new Line2D.Double(paramInt1, sub_7f6(paramInt2), paramInt3, sub_7f6(paramInt4));
    this.g2image.setColor(this.currentColor);
    this.g2image.draw(localDouble);
    repaint();
  }

  public void sub_77f(int paramInt1, int paramInt2, int paramInt3, int paramInt4, boolean paramBoolean)
  {
    sub_702(paramInt1 + paramInt3, paramInt2 + paramInt4);
    Rectangle2D.Double localDouble = new Rectangle2D.Double(paramInt1, sub_7f6(paramInt2) - paramInt4, paramInt3, paramInt4);
    this.g2image.setColor(this.currentColor);
    if (paramBoolean)
      this.g2image.fill(localDouble);
    else
      this.g2image.draw(localDouble);
    repaint();
  }

  private int sub_7f6(int paramInt)
  {
    return this.height - 1 - paramInt;
  }
}

/* Location:           C:\decompile\decompile\classes\
 * Qualified Name:     EasyJPanel
 * JD-Core Version:    0.6.0
 */