import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

const styles = {
  display: 'flex',
  alignItems: 'center',
  height: 80,
  padding: 15,
  fontSize: 24,
}

const Navbar = ({ rootStyles, titleStyles, title }) => (
  <div style={[styles, rootStyles]}>
    <div style={titleStyles}>{title}</div>
  </div>
)

Navbar.propTypes = {}
Navbar.defaultProps = {}

export default Radium(Navbar)
