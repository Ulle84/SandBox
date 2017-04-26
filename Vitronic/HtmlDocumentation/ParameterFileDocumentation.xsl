<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/">
    <html>
      <head>
        <title>
          <xsl:choose>
            <xsl:when test="local-name(/*[1]) = 'ViParameter'">
              <xsl:value-of select="local-name(ViParameter/*[1])"/> Parameter Description - Version <xsl:value-of select="ViParameter/*[1]/@Version"/>
            </xsl:when>
            <xsl:otherwise>
              No ViParameter File
            </xsl:otherwise>
          </xsl:choose>
        </title>
        <link rel="stylesheet" type="text/css" href="..\ViAcquiDocumentation\style.css" />
        <script type="text/javascript" src="..\ViAcquiDocumentation\script.js"/>
      </head>
      <body onload="init(1, 1)">
        <xsl:for-each select="ViParameter/*[1]/*">
          <h1>
            <xsl:value-of select="local-name()"/>
            <xsl:for-each select="@*">
              - <xsl:value-of select="local-name()"/> = <xsl:value-of select="." />
            </xsl:for-each>
          </h1>
          <table>
            <tr>
              <th>Parameter-Name</th>
              <th>Type</th>
              <th>Value</th>
              <th>Description</th>
              <th>Further Options</th>
            </tr>
            <xsl:for-each select=".//*">
              <tr>
                <td>
                  <xsl:variable name="padding" select="(count(ancestor::*) - 3) * 20" />
                  <div  style="display: inline-block; min-width: {$padding}px" />
                  <xsl:value-of select="local-name()"/>
                </td>
                <td>
                  <xsl:value-of select="./@Type"/>
                </td>
                <td>
                  <xsl:value-of select="./@Value"/>
                </td>
                <td>
                  <xsl:value-of select="./@Description"/>
                </td>
                <td>
                  <ul>
                    <xsl:for-each select="@*">
                      <xsl:choose>
                        <xsl:when test="local-name() = 'Type'" />
                        <xsl:when test="local-name() = 'Value'" />
                        <xsl:when test="local-name() = 'Description'" />
                        <xsl:when test="local-name() = 'Editor'" />
                        <xsl:otherwise>
                          <li>
                            <xsl:value-of select="local-name()"/>: <xsl:value-of select="."/>
                          </li>
                        </xsl:otherwise>
                      </xsl:choose>
                    </xsl:for-each>
                  </ul>
                </td>
              </tr>
            </xsl:for-each>
          </table>
        </xsl:for-each>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet> 