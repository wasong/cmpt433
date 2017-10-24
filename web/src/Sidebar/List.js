import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

import ListItem from './ListItem'

const List = props => (
  <div>
    <ListItem label="Dashboard" />
  </div>
)

List.propTypes = {}
List.defaultProps = {}

export default Radium(List)
