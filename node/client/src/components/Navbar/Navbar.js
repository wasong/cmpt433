import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

const styles = {
  display: 'flex',
  alignItems: 'center',
  height: 100,
  padding: '0 15px',
  fontSize: 24,
}

const Navbar = ({ rootStyles, titleStyles, title, icon }) => (
  <div style={[styles, rootStyles]}>
    {icon}
    <div style={titleStyles}>{title}</div>
  </div>
)

Navbar.propTypes = {}
Navbar.defaultProps = {}

export default Radium(Navbar)
