import React from 'react'
import Radium from 'radium'

const styles = {
  padding: '5px 15px',
  position: 'absolute',
  borderRadius: 25,
  top: '10px',
  left: '-10px',
}

const PaperBadge = ({ title, color }) => (
  <div style={[styles, { backgroundColor: color }]}>
    {title}
  </div>
)

PaperBadge.defaultProps = {
  title: '',
  color: 'green',
}

export default Radium(PaperBadge)
