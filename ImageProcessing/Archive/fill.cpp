template<typename T>
void Matrix<T>::fill(unsigned int z)
{
  /* perfect test region:

   *     *
   **   **
   * * * *
   *  *  *
   *******

  */

  // it's not enough to watch at 8er neighborhood!

  /* alternative idea
   * if type == bool -> create copy with unsigned char
   * go around edges of image -> find a pixel which is not set (if all edge pixels are set -> set all pixels in matrix)
   * floodfill on background with 4-neighborhood
   * everything which has not the floodfill value belongs to our object
   * TODO: ::fill(T value, ...) ?
   */

  if (typeid(T) != typeid(bool))
  {
    return; // not applicable
  }

  bool insideObject;
  unsigned int xStart;
  unsigned int xLastEdgePoint;

  std::vector<bool> neighbors(8);

  /* neighbors are set like freeman-code style
     321
     4*0
     567
  */

  for (unsigned int y = 0; y < m_height; y++)
  {
    insideObject = false;
    for (unsigned int x = 0; x < m_width; x++)
    {
      if (m_values[z][y][x])
      {
        xLastEdgePoint = x;

        std::cout << "y: " << y << " x: " << x;

        neighbors[0] = (x == m_width - 1                      ? false : m_values[z][y  ][x+1]);
        neighbors[1] = (x == m_width - 1 || y == 0            ? false : m_values[z][y-1][x+1]);
        neighbors[2] = (                    y == 0            ? false : m_values[z][y-1][x  ]);
        neighbors[3] = (x == 0           || y == 0            ? false : m_values[z][y-1][x-1]);
        neighbors[4] = (x == 0                                ? false : m_values[z][y  ][x-1]);
        neighbors[5] = (x == 0           || y == m_height - 1 ? false : m_values[z][y+1][x-1]);
        neighbors[6] = (                    y == m_height - 1 ? false : m_values[z][y+1][x  ]);
        neighbors[7] = (x == m_width - 1 || y == m_height - 1 ? false : m_values[z][y+1][x+1]);

        if (neighbors[4] && (neighbors[0] || neighbors[1]|| neighbors[2] || neighbors[3]))
        {
          // on horizontal line
          std::cout << " skipping horizontal line point" << std::endl;
          continue;
        }

        unsigned int qtyBottomNeighbors = 0;
        qtyBottomNeighbors += neighbors[5];
        qtyBottomNeighbors += neighbors[6];
        qtyBottomNeighbors += neighbors[7];

        unsigned int qtyTopNeighbors = 0;
        qtyTopNeighbors += neighbors[1];
        qtyTopNeighbors += neighbors[2];
        qtyTopNeighbors += neighbors[3];

        if (!insideObject && !neighbors[0] && !neighbors[4] && qtyBottomNeighbors >= 2)
        {
          // edge pointing up
          std::cout << " skipping edge pointing up" << std::endl;
          continue;
        }

        if (insideObject && !neighbors[0] && !neighbors[4] && qtyTopNeighbors >= 2)
        {
          // edge pointing down
          std::cout << " skipping edge pointing down" << std::endl;
          continue;
        }

        if (insideObject)
        {
          for (unsigned int xMark = xStart; xMark < x; xMark++)
          {
            m_values[z][y][xMark] = true;
            insideObject = false;
          }
          std::cout << " found end of line" << std::endl;
        }
        else
        {
          xStart = x;
          insideObject = true;
          std::cout << " found begin of line" << std::endl;
        }
      }

      if (x == m_width - 1 && insideObject)
      {
        // end of line and still inside object -> moving back to last edge -> and draw line
        for (unsigned int xMark = xStart; xMark < xLastEdgePoint; xMark++)
        {
          m_values[z][y][xMark] = true;
          insideObject = false;
          std::cout << " end of line marked from " << xStart << " to " << xLastEdgePoint << std::endl;
        }
      }
    }
  }
}