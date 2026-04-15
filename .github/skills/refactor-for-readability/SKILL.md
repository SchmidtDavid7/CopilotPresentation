---
name: refactor-for-readability
description: Refactor code to improve readability, naming, structure, and maintainability without changing behavior. Use this when cleaning up code or preparing a codebase for better AI collaboration.
---

# Refactor for Readability

Use this skill when improving code quality without changing external behavior.

## Goals

- Improve readability
- Improve naming
- Reduce local complexity
- Preserve behavior
- Make the code easier for both humans and AI to understand

## Preferred refactoring principles

- Prefer small, focused functions
- Extract mixed responsibilities into separate helpers
- Replace vague names with explicit ones
- Preserve public behavior unless explicitly asked otherwise
- Prefer clear control flow over clever compactness
- Reduce hidden side effects
- Keep interfaces clean and minimal

## What to look for

- Long functions doing multiple things
- Weak or ambiguous names
- Duplicate logic
- Deep nesting
- Mixed validation, business logic, and side effects in one place
- Large blocks that can be expressed as intent-revealing helper functions

## Constraints

- Do not introduce unrelated architectural changes
- Do not change behavior intentionally
- Do not rewrite everything just because it could be cleaner
- Keep the diff focused and reviewable

## Output expectations

When reporting your work:

- Summarize what was refactored
- Explain why the new structure is easier to understand
- Mention any areas where behavior preservation could not be fully verified